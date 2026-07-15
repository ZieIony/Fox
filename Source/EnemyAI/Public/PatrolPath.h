#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SplineComponent.h>
#include "PatrolDirection.h"

#include "PatrolPath.generated.h"

UCLASS()
class ENEMYAI_API APatrolPath: public AActor {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USplineComponent* Spline;

	APatrolPath();

	UFUNCTION(BlueprintPure)
	int GetFirstPointIndex(EPatrolDirection direction);

	UFUNCTION(BlueprintPure)
	int GetNextPointIndex(int currentPointIndex, EPatrolDirection direction);

	UFUNCTION(BlueprintPure)
	bool IsLastPointIndex(int pointIndex, EPatrolDirection direction);

	UFUNCTION(BlueprintPure)
	FVector GetPointLocation(int pointIndex);
};
