#pragma once

#include "CoreMinimal.h"
#include "PowerSourceState.generated.h"

UENUM(BlueprintType)
enum class EPowerSourceState: uint8 {
	Working UMETA(DisplayName = "Working"),
	Idle UMETA(DisplayName = "Idle"),
	Broken UMETA(DisplayName = "Broken")
};
