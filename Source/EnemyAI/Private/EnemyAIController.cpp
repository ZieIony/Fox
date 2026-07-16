#include "EnemyAIController.h"

#include <GameFramework/CharacterMovementComponent.h>

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
