#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "HeatSourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOX_API UHeatSourceComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinHeatSize = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHeatSize = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeatChangeSpeed = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentHeatSize = 2;

	UHeatSourceComponent();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	/**
	* returns true if updated heat size, false otherwise
	**/
	bool UpdateSize(float DeltaTime) {
		if (IsActive() && CurrentHeatSize != MaxHeatSize) {
			CurrentHeatSize = std::max(MinHeatSize, std::min(CurrentHeatSize + HeatChangeSpeed * DeltaTime, MaxHeatSize));
		} else if (!IsActive() && CurrentHeatSize != MinHeatSize) {
			CurrentHeatSize = std::max(MinHeatSize, std::min(CurrentHeatSize - HeatChangeSpeed * DeltaTime, MaxHeatSize));
		} else {
			return false;
		}

		SetWorldScale3D(FVector(CurrentHeatSize, CurrentHeatSize, CurrentHeatSize));
		return true;
	}
};
