#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "EnemyAIState.h"

#include "BTDecoratorIsInState.generated.h"

UCLASS()
class ENEMYAI_API UBTDecoratorIsInState: public UBTDecorator {
	GENERATED_BODY()

protected:
	UBehaviorTreeComponent* owner = nullptr;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyAIState State;

	UBTDecoratorIsInState() {
		bNotifyBecomeRelevant = true;
		bNotifyCeaseRelevant = true;
	}

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UFUNCTION()
	void OnStateChanged(EEnemyAIState newState);
};
