#include "BTTaskPerformAction.h"

#include <EnemyAIController.h>

void UBTTaskPerformAction::onActionFinished(EAIActionResult result) {
	if (aiController)
		aiController->OnActionFinished.RemoveDynamic(this, &UBTTaskPerformAction::onActionFinished);
	FinishLatentTask(*owner, [result]() {
		if (result == EAIActionResult::Succeeded) {
			return EBTNodeResult::Succeeded;
		} else if (result == EAIActionResult::Failed) {
			return EBTNodeResult::Failed;
		} else {
			return EBTNodeResult::Aborted;
		}
	}());
	owner = nullptr;
	aiController = nullptr;
}

void UBTTaskPerformAction::SetOwner(AActor* ActorOwner) {
	if (owner && aiController) {
		const EBTTaskStatus::Type Status = owner->GetTaskStatus(this);
		if (Status == EBTTaskStatus::Active) {
			FinishLatentTask(*owner, EBTNodeResult::Aborted);
			onActionFinished(EAIActionResult::Cancelled);
			aiController->OnActionFinished.RemoveDynamic(this, &UBTTaskPerformAction::onActionFinished);
		}
		owner = nullptr;
		aiController = nullptr;
	}
}

EBTNodeResult::Type UBTTaskPerformAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	owner = &OwnerComp;
	aiController = (AEnemyAIController*)OwnerComp.GetAIOwner();
	aiController->OnActionFinished.AddDynamic(this, &UBTTaskPerformAction::onActionFinished);
	aiController->PerformAction();
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTaskPerformAction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	aiController->OnActionFinished.RemoveDynamic(this, &UBTTaskPerformAction::onActionFinished);
	aiController->CancelAction();
	owner = nullptr;
	aiController = nullptr;
	return EBTNodeResult::Aborted;
}

void UBTTaskPerformAction::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) {
	if (aiController)
		aiController->OnActionFinished.RemoveDynamic(this, &UBTTaskPerformAction::onActionFinished);
}
