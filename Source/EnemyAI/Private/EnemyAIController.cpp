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

AEnemyAIController::AEnemyAIController() {
	aiPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*aiPerceptionComponent);
	aiPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	sightConfig->SightRadius = 500;
	sightConfig->LoseSightRadius = 700;
	sightConfig->PeripheralVisionAngleDegrees = 60;
	sightConfig->SetMaxAge(5);
	aiPerceptionComponent->ConfigureSense(*sightConfig);

	hearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	hearingConfig->HearingRange = 800;
	hearingConfig->SetMaxAge(5);
	aiPerceptionComponent->ConfigureSense(*hearingConfig);

	damageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	damageConfig->SetMaxAge(5);
	aiPerceptionComponent->ConfigureSense(*damageConfig);

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
	LastKnownPlayer = DamageDealer;
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
	if (IsValid(AwarenessMeterWidget) && IsValid(LastKnownPlayer)) {
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
