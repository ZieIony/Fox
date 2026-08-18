#include "EnemyAIController.h"

#include <GameFramework/CharacterMovementComponent.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>
#include <Perception/AISenseConfig_Damage.h>
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>
#include "AwarenessMeterWidget.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <cmath>
#include <numbers>

bool AEnemyAIController::WasSuccessfullySensed(const FActorPerceptionBlueprintInfo& info) {
	for (auto& sense : info.LastSensedStimuli) {
		if (sense.WasSuccessfullySensed())
			return true;
	}
	return false;
}

void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors) {
	for (auto& actor : UpdatedActors) {
		FActorPerceptionBlueprintInfo info;
		aiPerceptionComponent->GetActorsPerception(actor, info);
		if (info.bIsHostile && WasSuccessfullySensed(info)) {
			if (LastKnownPlayer != actor) {
				LastKnownPlayer = actor;
				GetBlackboardComponent()->SetValueAsObject("LastKnownPlayer", LastKnownPlayer);
				LastKnownPosition = actor->GetActorLocation();
				GetBlackboardComponent()->SetValueAsVector("LastKnownPosition", LastKnownPosition);
			}
			return;
		}
	}
}

void AEnemyAIController::IncreaseAwarenessLevel(float DeltaTime, float AwarenessUpdate) {
	if (PerceptionState == EPerceptionState::Idle || PerceptionState == EPerceptionState::Suspicious) {
		AwarenessLevel = std::max(0.0f, std::min(AwarenessLevel + DeltaTime * AwarenessUpdate, 1.0f));
	} if (PerceptionState == EPerceptionState::Alerted) {
		AwarenessLevel = 1.0f;
	}

	if (AwarenessLevel == 1.0f && PerceptionState != EPerceptionState::Engaged) {
		AwarenessMeterWidget->SetAlerted(true);
		SetPerceptionState(EPerceptionState::Engaged);
	} else if (AwarenessLevel > 0.25f && PerceptionState == EPerceptionState::Idle) {
		SetPerceptionState(EPerceptionState::Suspicious);
	} else if (AwarenessLevel == 0.0f && PerceptionState != EPerceptionState::Idle) {
		AwarenessMeterWidget->SetAlerted(false);
		SetPerceptionState(EPerceptionState::Idle);
	}

	if (AwarenessLevel > 0.0f) {
		AwarenessMeterWidget->SetVisibility(ESlateVisibility::Visible);
		AwarenessMeterWidget->SetAwarenessLevel(AwarenessLevel);
	}
}

void AEnemyAIController::DecreaseAwarenessLevel(float DeltaTime) {
	if (PerceptionState == EPerceptionState::Suspicious) {
		AwarenessLevel = std::max(0.0f, std::min(AwarenessLevel - DeltaTime * 0.5f, 1.0f));
	} if (PerceptionState == EPerceptionState::Alerted) {
		AwarenessLevel = std::max(0.0f, std::min(AwarenessLevel - DeltaTime * 0.25f, 1.0f));
	}

	if (PerceptionState == EPerceptionState::Engaged) {
		SetPerceptionState(EPerceptionState::Alerted);
	} else if (AwarenessLevel == 0.0f && PerceptionState != EPerceptionState::Idle) {
		AwarenessMeterWidget->SetAlerted(false);
		AwarenessMeterWidget->SetVisibility(ESlateVisibility::Collapsed);
		SetPerceptionState(EPerceptionState::Idle);
	}

	if (AwarenessLevel > 0.0f)
		AwarenessMeterWidget->SetAwarenessLevel(AwarenessLevel);
}

void AEnemyAIController::UpdateAwarenessLevel(float DeltaTime) {
	if (!aiPerceptionComponent->IsActive())
		return;

	FActorPerceptionBlueprintInfo info;
	aiPerceptionComponent->GetActorsPerception(LastKnownPlayer, info);
	float awarenessUpdate = 0.0f;
	for (auto& sense : info.LastSensedStimuli) {
		if (sense.WasSuccessfullySensed())
			awarenessUpdate += sense.Strength;
	}
	if (awarenessUpdate != 0.0f) {
		IncreaseAwarenessLevel(DeltaTime, awarenessUpdate);
	} else {
		DecreaseAwarenessLevel(DeltaTime);
	}
}

AEnemyAIController::AEnemyAIController() {
	aiPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*aiPerceptionComponent);
	aiPerceptionComponent->Activate();
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

void AEnemyAIController::SetPerceptionState(EPerceptionState NewState) {
	if (PerceptionState != NewState) {
		PerceptionState = NewState;
		GetBlackboardComponent()->SetValueAsEnum("PerceptionState", (uint8)PerceptionState);
		OnPerceptionStateChanged.Broadcast(PerceptionState);
	}
}

void AEnemyAIController::PerformAction() {
	OnActionStarted.Broadcast();
}

void AEnemyAIController::FinishAction() {
	OnActionFinished.Broadcast(EAIActionResult::Succeeded);
}

void AEnemyAIController::CancelAction() {
	OnActionFinished.Broadcast(EAIActionResult::Cancelled);
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
		UpdateAwarenessLevel(DeltaTime);

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
