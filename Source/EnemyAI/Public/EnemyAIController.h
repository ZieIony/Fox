#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIActionResult.h"
#include "PerceptionState.h"
#include <MovementType.h>
#include <Perception/AIPerceptionTypes.h>
#include <Perception/AIPerceptionComponent.h>

#include "EnemyAIController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIActionStarted);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIActionFinished, EAIActionResult, Result);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPerceptionStateChanged, EPerceptionState, NewPerceptionState);

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

	bool WasSuccessfullySensed(const FActorPerceptionBlueprintInfo& info);

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	void IncreaseAwarenessLevel(float DeltaTime, float AwarenessUpdate);

	void DecreaseAwarenessLevel(float DeltaTime);

	void UpdateAwarenessLevel(float DeltaTime);

public:
	AEnemyAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> LastKnownPlayer = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector LastKnownPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AwarenessLevel = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAwarenessMeterWidget> AwarenessMeterWidget;

	// state
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPerceptionState PerceptionState;

	UFUNCTION(BlueprintCallable)
	void SetPerceptionState(EPerceptionState NewState);

	UPROPERTY(BlueprintAssignable)
	FPerceptionStateChanged OnPerceptionStateChanged;

	UPROPERTY(BlueprintAssignable)
	FAIActionStarted OnActionStarted;

	UPROPERTY(BlueprintAssignable)
	FAIActionFinished OnActionFinished;

	UFUNCTION(BlueprintCallable)
	void PerformAction();

	UFUNCTION(BlueprintCallable)
	void FinishAction();

	UFUNCTION(BlueprintCallable)
	void CancelAction();

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
