#include "BTTaskSetState.h"
#include <BehaviorTree/BlackboardComponent.h>

EBTNodeResult::Type UBTTaskSetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto blackboard = OwnerComp.GetBlackboardComponent();
	blackboard->SetValueAsEnum(StateKey.SelectedKeyName, (uint8)State);
	return EBTNodeResult::Succeeded;
}
