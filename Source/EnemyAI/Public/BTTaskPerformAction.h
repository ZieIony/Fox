#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "AIActionResult.h"

#include "BTTaskPerformAction.generated.h"

class AEnemyAIController;

UCLASS()
class ENEMYAI_API UBTTaskPerformAction: public UBTTaskNode {
	GENERATED_BODY()

private:
	AEnemyAIController* aiController = nullptr;
	UBehaviorTreeComponent* owner = nullptr;

	UBTTaskPerformAction() {
		bCreateNodeInstance = true;
	}

	UFUNCTION()
	void onActionFinished(EAIActionResult result);

protected:
	virtual void SetOwner(AActor* ActorOwner) override;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;
};
