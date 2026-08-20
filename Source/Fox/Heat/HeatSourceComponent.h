#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "HeatSourceState.h"
#include <GameplayTagAssetInterface.h>
#include "PowerSourceType.h"

#include "HeatSourceComponent.generated.h"

class APowerSource;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FOX_API UHeatSourceComponent: public UStaticMeshComponent, public IGameplayTagAssetInterface {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float MinHeatSize = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float MaxHeatSize = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float HeatChangeSpeed = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float CurrentHeatSize = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FGameplayTagContainer GameplayTags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	EHeatSourceState HeatSourceState = EHeatSourceState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	APowerSource* PowerSource;

	UHeatSourceComponent();

	UFUNCTION(BlueprintCallable)
	bool StartHeatSource();

	bool StartHeatSource(APowerSource* powerSource);

	UFUNCTION(BlueprintCallable)
	bool StopHeatSource() {
		if (HeatSourceState == EHeatSourceState::Broken || HeatSourceState == EHeatSourceState::Idle)
			return false;
		HeatSourceState = EHeatSourceState::Idle;
		return true;
	}

	UFUNCTION(BlueprintCallable)
	bool BreakHeatSource() {
		if (HeatSourceState == EHeatSourceState::Broken)
			return false;
		HeatSourceState = EHeatSourceState::Broken;
		return true;
	}

	/**
	* returns true if updated heat size, false otherwise
	**/
	bool UpdateSize(float DeltaTime) {
		if (HeatSourceState == EHeatSourceState::Working && CurrentHeatSize != MaxHeatSize) {
			CurrentHeatSize = std::max(MinHeatSize, std::min(CurrentHeatSize + HeatChangeSpeed * DeltaTime, MaxHeatSize));
		} else if (HeatSourceState != EHeatSourceState::Working && CurrentHeatSize != MinHeatSize) {
			CurrentHeatSize = std::max(MinHeatSize, std::min(CurrentHeatSize - HeatChangeSpeed * DeltaTime, MaxHeatSize));
		} else {
			return false;
		}

		SetWorldScale3D(FVector(CurrentHeatSize, CurrentHeatSize, CurrentHeatSize));
		return true;
	}

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override {
		TagContainer.AppendTags(this->GameplayTags);
	}

	virtual void OnRegister() override;
};
