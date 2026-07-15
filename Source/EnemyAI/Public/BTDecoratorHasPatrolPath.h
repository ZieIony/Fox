#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "BTDecoratorHasPatrolPath.generated.h"

UCLASS()
class ENEMYAI_API UBTDecoratorHasPatrolPath: public UBTDecorator {
	GENERATED_BODY()

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
