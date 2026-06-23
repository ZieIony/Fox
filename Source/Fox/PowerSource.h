#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagsClasses.h"
#include "NativeGameplayTags.h"
#include "PowerSourceState.h"
#include "PowerSourceType.h"
#include "PowerSource.generated.h"

class APowerSource;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPowerSourceOnWorkingChanged, APowerSource*, PowerSource, bool, Working);

UCLASS()
class FOX_API APowerSource: public AActor, public IGameplayTagAssetInterface {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Gameplay")
	FPowerSourceOnWorkingChanged OnWorkingChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FGameplayTagContainer GameplayTags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	EPowerSourceState PowerSourceState = EPowerSourceState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	EPowerSourceType PowerSourceType = EPowerSourceType::Red;

	APowerSource();

	inline bool isWorking() const {
		return PowerSourceState == EPowerSourceState::Working;
	}

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void StartPowerSource() {
		if (PowerSourceState == EPowerSourceState::Idle) {
			PowerSourceState = EPowerSourceState::Working;
			OnWorkingChanged.Broadcast(this, true);
		}
	}

	void StopPowerSource() {
		if (PowerSourceState == EPowerSourceState::Working) {
			PowerSourceState = EPowerSourceState::Idle;
			OnWorkingChanged.Broadcast(this, false);
		}
	}

	void BreakPowerSource() {
		auto prevState = PowerSourceState;
		PowerSourceState = EPowerSourceState::Broken;
		if (prevState == EPowerSourceState::Working)
			OnWorkingChanged.Broadcast(this, false);
	}

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override {
		TagContainer.AppendTags(this->GameplayTags);
	}
};
