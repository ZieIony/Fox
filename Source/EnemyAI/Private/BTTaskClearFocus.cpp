#include "BTTaskClearFocus.h"

#include <EnemyAIController.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

EBTNodeResult::Type UBTTaskClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto aiController = (AEnemyAIController*)OwnerComp.GetAIOwner();
	aiController->ClearFocus(EAIFocusPriority::Gameplay);
	return EBTNodeResult::Succeeded;
}
