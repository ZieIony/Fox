#include "BTDecoratorIsInState.h"
#include <BehaviorTree/BehaviorTreeComponent.h>
#include "EnemyAIController.h"

void UBTDecoratorIsInState::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	owner = &OwnerComp;
	auto aiController = (AEnemyAIController*)OwnerComp.GetAIOwner();
	aiController->OnStateChangedEvent.AddDynamic(this, &UBTDecoratorIsInState::OnStateChanged);
}

void UBTDecoratorIsInState::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto aiController = (AEnemyAIController*)OwnerComp.GetAIOwner();
	aiController->OnStateChangedEvent.RemoveDynamic(this, &UBTDecoratorIsInState::OnStateChanged);
}

bool UBTDecoratorIsInState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	auto aiController = (AEnemyAIController*)OwnerComp.GetAIOwner();
	return aiController->AIState == State;
}

void UBTDecoratorIsInState::OnStateChanged(EEnemyAIState newState) {
	if (State == newState) {
		owner->RequestExecution(this);
	} else {
		ConditionalFlowAbort(*owner, EBTDecoratorAbortRequest::ConditionResultChanged);
	}
}
