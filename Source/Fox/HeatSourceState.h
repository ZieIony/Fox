#pragma once

#include "CoreMinimal.h"
#include "HeatSourceState.generated.h"

UENUM(BlueprintType)
enum class EHeatSourceState: uint8 {
	Working UMETA(DisplayName = "Working"),
	Idle UMETA(DisplayName = "Idle"),
	Broken UMETA(DisplayName = "Broken")
};
