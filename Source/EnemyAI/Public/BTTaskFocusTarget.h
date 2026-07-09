#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTaskFocusTarget.generated.h"

UCLASS()
class ENEMYAI_API UBTTaskFocusTarget: public UBTTaskNode {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Keys")
	FBlackboardKeySelector AttackTargetKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
