#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIActionResult.h"
#include "EnemyAIState.h"
#include <MovementType.h>
#include <Perception/AIPerceptionTypes.h>

#include "EnemyAIController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyStateChanged, EEnemyAIState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIActionStarted);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIActionFinished, EAIActionResult, Result);

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;
class UAwarenessMeterWidget;

UCLASS()
class ENEMYAI_API AEnemyAIController: public AAIController {
	GENERATED_BODY()

private:
	UAIPerceptionComponent* aiPerceptionComponent;

	UAISenseConfig_Sight* sightConfig;

	UAISenseConfig_Hearing* hearingConfig;

	UAISenseConfig_Damage* damageConfig;

	AActor* LastKnownPlayer = nullptr;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	void UpdateAwarenessLevel(float AwarenessUpdate);

public:
	AEnemyAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AwarenessLevel = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAwarenessMeterWidget> AwarenessMeterWidget;

	// state
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

	UFUNCTION(BlueprintCallable)
	void ReportDamage(AActor* DamageDealer);

	// movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float WalkSpeed = 150;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RunSpeed = 300;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SprintSpeed = 600;

	UFUNCTION(BlueprintCallable)
	void SetMovementType(EMovementType movementType);

	virtual void Tick(float DeltaTime) override;
};
