#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIActionResult.h"
#include "EnemyAIState.h"
#include <MovementType.h>

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

	// movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float WalkSpeed = 150;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RunSpeed = 300;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SprintSpeed = 600;

	UFUNCTION(BlueprintCallable)
	void SetMovementType(EMovementType movementType);
};
