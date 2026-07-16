#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MovementType.h"
#include "BTTaskSetMovementType.generated.h"

UCLASS()
class ENEMYAI_API UBTTaskSetMovementType: public UBTTaskNode {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMovementType movementType = EMovementType::WALKING;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
