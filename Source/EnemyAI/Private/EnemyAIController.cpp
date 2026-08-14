#include "EnemyAIController.h"

#include <GameFramework/CharacterMovementComponent.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>
#include <Perception/AISenseConfig_Damage.h>
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>
#include "AwarenessMeterWidget.h"

#include <cmath>
#include <numbers>

void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors) {
	for (auto& actor : UpdatedActors) {
		FActorPerceptionBlueprintInfo info;
		aiPerceptionComponent->GetActorsPerception(actor, info);
		if (info.bIsHostile) {
			if (LastKnownPlayer != actor) {
				AwarenessLevel = 0;
				LastKnownPlayer = actor;
			}
			return;
		}
	}
}

void AEnemyAIController::UpdateAwarenessLevel(float AwarenessUpdate) {
	AwarenessLevel = std::max(0.0f, std::min(AwarenessLevel + AwarenessUpdate, 1.0f));
	AwarenessMeterWidget->SetAwarenessLevel(AwarenessLevel);

	if (AwarenessLevel == 1.0f) {
		AwarenessMeterWidget->SetAlerted(true);
	} else if (AwarenessLevel == 0.0f) {
		AwarenessMeterWidget->SetAlerted(false);
	}

	if (AwarenessLevel > 0.0f) {
		AwarenessMeterWidget->SetVisibility(ESlateVisibility::Visible);
	} else {
		AwarenessMeterWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

AEnemyAIController::AEnemyAIController() {
	aiPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*aiPerceptionComponent);
	aiPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	sightConfig->SightRadius = 500;
	sightConfig->LoseSightRadius = 700;
	sightConfig->PeripheralVisionAngleDegrees = 60;
	sightConfig->SetMaxAge(1);
	aiPerceptionComponent->ConfigureSense(*sightConfig);

	hearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	hearingConfig->HearingRange = 800;
	hearingConfig->SetMaxAge(1);
	aiPerceptionComponent->ConfigureSense(*hearingConfig);

	damageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	damageConfig->SetMaxAge(1);
	aiPerceptionComponent->ConfigureSense(*damageConfig);

	aiPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);

	FGenericTeamId enemyTeamId = 1;
	SetGenericTeamId(enemyTeamId);
}

void AEnemyAIController::Attack() {
	AIState = EEnemyAIState::Attacking;
	OnAttackStarted.Broadcast();
}

void AEnemyAIController::FinishAttack() {
	AIState = EEnemyAIState::Idle;
	OnAttackFinished.Broadcast(EAIActionResult::Succeeded);
}

void AEnemyAIController::CancelAttack() {
	AIState = EEnemyAIState::Idle;
	OnAttackFinished.Broadcast(EAIActionResult::Cancelled);
}

void AEnemyAIController::ReportDamage(AActor* DamageDealer) {
	UAISense_Damage::ReportDamageEvent(GetPawn()->GetWorld(), GetPawn(), DamageDealer, 1, DamageDealer->GetActorLocation(), DamageDealer->GetActorLocation());
}

void AEnemyAIController::SetMovementType(EMovementType movementType) {
	auto movementComponent = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent());
	if (movementType == EMovementType::WALKING) {
		movementComponent->MaxWalkSpeed = WalkSpeed;
	} else if (movementType == EMovementType::RUNNING) {
		movementComponent->MaxWalkSpeed = RunSpeed;
	} else if (movementType == EMovementType::SPRINTING) {
		movementComponent->MaxWalkSpeed = SprintSpeed;
	}
}

void AEnemyAIController::Tick(float DeltaTime) {
	if (IsValid(GetPawn()))
		SetControlRotation(GetPawn()->GetActorRotation());

	if (IsValid(AwarenessMeterWidget) && IsValid(LastKnownPlayer)) {
		FActorPerceptionBlueprintInfo info;
		aiPerceptionComponent->GetActorsPerception(LastKnownPlayer, info);
		float awarenessUpdate = 0.0f;
		for (auto& sense : info.LastSensedStimuli) {
			if (sense.WasSuccessfullySensed()) {
				awarenessUpdate += DeltaTime * sense.Strength;
			}
		}
		if (awarenessUpdate != 0.0f) {
			UpdateAwarenessLevel(awarenessUpdate);
		} else {
			UpdateAwarenessLevel(DeltaTime * -0.5f);
		}

		auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		auto playerLocation = LastKnownPlayer->GetActorLocation();
		auto enemyLocation = GetPawn()->GetActorLocation();
		FVector2D playerScreenLocation, enemyScreenLocation;
		playerController->ProjectWorldLocationToScreen(playerLocation, playerScreenLocation, true);
		playerController->ProjectWorldLocationToScreen(enemyLocation, enemyScreenLocation, true);
		if (playerScreenLocation != enemyScreenLocation) {
			float angle = std::atan2(enemyScreenLocation.Y - playerScreenLocation.Y, enemyScreenLocation.X - playerScreenLocation.X);
			AwarenessMeterWidget->SetAngle(angle * 180.0f / std::numbers::pi + 90.0f);
		}
	}
}
