#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolMode.h"
#include "PatrolDirection.h"

#include "BTTaskPatrolPath.generated.h"

class APatrolPath;

UCLASS()
class ENEMYAI_API UBTTaskPatrolPath: public UBTTaskNode {
	GENERATED_BODY()

private:
	EPatrolDirection ReversePatrolDirectionIfNeeded(UBlackboardComponent* blackboard, EPatrolDirection direction);

	void MoveToNextPoint(
		UBlackboardComponent* blackboard,
		APatrolPath* patrolPath,
		int currentPatrolPointIndex,
		EPatrolDirection currentPatrolDirection
	);

	EBTNodeResult::Type ProcessStep(APatrolPath* patrolPath, UBlackboardComponent* blackboard, int currentPatrolPointIndex);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Keys")
	FBlackboardKeySelector CurrentPatrolPointIndexKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Keys")
	FBlackboardKeySelector CurrentPatrolDirectionKey;

	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AcceptableRadius;

	UPROPERTY(Category = Node, EditAnywhere)
	EPatrolMode PatrolMode;

	UPROPERTY(Category = Node, EditAnywhere)
	bool ReversePatrolDirectionAtCompletion;

	UBTTaskPatrolPath() {
		bNotifyTick = true;
	}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
