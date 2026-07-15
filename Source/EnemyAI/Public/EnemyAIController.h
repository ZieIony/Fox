#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIActionResult.h"
#include "EnemyAIState.h"

#include "EnemyAIController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyStateChanged, EEnemyAIState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIActionStarted);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIActionFinished, EAIActionResult, Result);

UCLASS()
class ENEMYAI_API AEnemyAIController: public AAIController {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEnemyAIState AIState;

	UPROPERTY(BlueprintAssignable)
	FOnEnemyStateChanged OnStateChangedEvent;

	UPROPERTY(BlueprintAssignable)
	FAIActionStarted OnAttackStarted;

	UPROPERTY(BlueprintAssignable)
	FAIActionFinished OnAttackFinished;

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void FinishAttack();

	UFUNCTION(BlueprintCallable)
	void CancelAttack();
};
