#include "BTTaskAttack.h"

#include <EnemyAIController.h>

void UBTTaskAttack::onAttackFinished(EAIActionResult result) {
	if (aiController)
		aiController->OnAttackFinished.RemoveDynamic(this, &UBTTaskAttack::onAttackFinished);
	FinishLatentTask(*owner, [result]() {
		if (result == EAIActionResult::Succeeded) {
			return EBTNodeResult::Succeeded;
		} else if (result == EAIActionResult::Failed) {
			return EBTNodeResult::Failed;
		} else {
			return EBTNodeResult::Aborted;
		}
	}());
}

void UBTTaskAttack::SetOwner(AActor* ActorOwner) {
	if (owner && aiController) {
		const EBTTaskStatus::Type Status = owner->GetTaskStatus(this);
		if (Status == EBTTaskStatus::Active) {
			FinishLatentTask(*owner, EBTNodeResult::Aborted);
			onAttackFinished(EAIActionResult::Cancelled);
			aiController->OnAttackFinished.RemoveDynamic(this, &UBTTaskAttack::onAttackFinished);
		}
		owner = nullptr;
		aiController = nullptr;
	}
}

EBTNodeResult::Type UBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	owner = &OwnerComp;
	aiController = (AEnemyAIController*)OwnerComp.GetAIOwner();
	aiController->OnAttackFinished.AddDynamic(this, &UBTTaskAttack::onAttackFinished);
	aiController->Attack();
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTaskAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	aiController->OnAttackFinished.RemoveDynamic(this, &UBTTaskAttack::onAttackFinished);
	aiController->CancelAttack();
	owner = nullptr;
	aiController = nullptr;
	return EBTNodeResult::Aborted;
}
