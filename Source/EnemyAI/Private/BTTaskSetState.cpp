#include "BTTaskSetState.h"
#include <EnemyAIController.h>

EBTNodeResult::Type UBTTaskSetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    auto aiController = (AEnemyAIController*)OwnerComp.GetOwner();
    //aiController->setState(state);
    return EBTNodeResult::Succeeded;
}
