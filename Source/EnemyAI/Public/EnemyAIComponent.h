#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAIController.h"
#include "PatrolPath.h"
#include <AwarenessMeterWidget.h>

#include "EnemyAIComponent.generated.h"

class AAIController;
class AController;
class APawn;

UCLASS(ClassGroup = AI)
class ENEMYAI_API UEnemyAIComponent: public UActorComponent {
	GENERATED_BODY()

private:
	TObjectPtr<UAwarenessMeterWidget> AwarenessMeterWidget;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAwarenessMeterWidget> AwarenessMeterWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APatrolPath> PatrolPath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AEnemyAIController> EnemyAIController;
};
