#include "EnemyAIController.h"

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
