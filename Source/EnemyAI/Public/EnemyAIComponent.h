#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAIController.h"
#include "PatrolPath.h"

#include "EnemyAIComponent.generated.h"

class AAIController;
class AController;
class APawn;

UCLASS(ClassGroup = AI)
class ENEMYAI_API UEnemyAIComponent: public UActorComponent {
	GENERATED_BODY()

protected:
	UPROPERTY(transient)
	TObjectPtr<AEnemyAIController> AIController;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APatrolPath> PatrolPath;

	virtual void OnRegister() override;

	AEnemyAIController* GetAIController() const {
		return AIController;
	}
};
