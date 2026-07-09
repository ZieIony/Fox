#include "BTTaskFocusTarget.h"

#include <EnemyAIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

EBTNodeResult::Type UBTTaskFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto aiController = (AEnemyAIController*)OwnerComp.GetAIOwner();
	auto owner = (ACharacter*)OwnerComp.GetOwner();
	auto attackTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AttackTargetKey.SelectedKeyName));
	if (IsValid(attackTarget))
		aiController->SetFocus(attackTarget);
	return EBTNodeResult::Succeeded;
}
