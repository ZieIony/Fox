#pragma once

#include "CoreMinimal.h"
#include "PowerSourceType.generated.h"

UENUM(BlueprintType)
enum class EPowerSourceType: uint8 {
	Red UMETA(DisplayName = "Red power source"),
	Green UMETA(DisplayName = "Green power source"),
	Blue UMETA(DisplayName = "Blue power source")
};
