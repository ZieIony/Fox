#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "HeatSourceComponent.h"
#include "PowerSource.h"
#include "FoxGameplayTagManager.h"
#include "HeatSubsystem.generated.h"

/**
 *
 */
UCLASS()
class FOX_API UHeatSubsystem: public UTickableWorldSubsystem {
	GENERATED_BODY()

private:
	TArray<UHeatSourceComponent*> heatSources;
	TArray<APowerSource*> powerSources;

	UFUNCTION()
	void PowerSourceOnWorkingChanged(APowerSource* powerSource, bool working);

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

	UHeatSourceComponent* GetFirstHeatSource(EPowerSourceType type) {
		for (auto& source : heatSources) {
			if (source->PowerSource && source->PowerSource->PowerSourceType == type)
				return source;
		}
		return nullptr;
	}

	void ManagePowerSource(APowerSource* powerSource) {
		powerSources.Add(powerSource);
		powerSource->OnWorkingChanged.AddDynamic(this, &UHeatSubsystem::PowerSourceOnWorkingChanged);
	}

	void RemovePowerSource(APowerSource* powerSource) {
		powerSources.Remove(powerSource);
	}

	APowerSource* GetFirstPowerSource(EPowerSourceType type) {
		for (auto& source : powerSources) {
			if (source->PowerSourceType == type)
				return source;
		}
		return nullptr;
	}

	virtual void Tick(float DeltaTime) override;
};
