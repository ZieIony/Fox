#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyAIState.h"

#include "BTTaskSetState.generated.h"

UCLASS()
class ENEMYAI_API UBTTaskSetState: public UBTTaskNode {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyAIState State = EEnemyAIState::Patrolling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Keys")
	FBlackboardKeySelector StateKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
