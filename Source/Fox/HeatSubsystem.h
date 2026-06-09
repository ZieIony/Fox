#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "HeatSourceComponent.h"
#include "HeatSubsystem.generated.h"

/**
 *
 */
UCLASS()
class FOX_API UHeatSubsystem: public UTickableWorldSubsystem {
	GENERATED_BODY()

private:
	TArray<UHeatSourceComponent*> heatSources;

public:
	virtual TStatId GetStatId() const override {
		RETURN_QUICK_DECLARE_CYCLE_STAT(UHeatSubsystem, STATGROUP_Tickables);
	}

	void ManageHeatSource(UHeatSourceComponent* heatSource) {
		heatSources.Add(heatSource);
	}

	void RemoveHeatSource(UHeatSourceComponent* heatSource) {
		heatSources.Remove(heatSource);
	}

	virtual void Tick(float DeltaTime) override;
};
