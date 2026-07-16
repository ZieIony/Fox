#include "BTTaskSetMovementType.h"
#include <EnemyAIController.h>

EBTNodeResult::Type UBTTaskSetMovementType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    auto aiController = (AEnemyAIController*)OwnerComp.GetOwner();
    aiController->SetMovementType(movementType);
    return EBTNodeResult::Succeeded;
}
