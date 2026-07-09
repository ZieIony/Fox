#pragma once

#include "CoreMinimal.h"
#include "AIActionResult.generated.h"

UENUM(BlueprintType)
enum class EAIActionResult: uint8 {
	Succeeded UMETA(DisplayName = "Succeeded"),
	Failed UMETA(DisplayName = "Failed"),
	Cancelled UMETA(DisplayName = "Cancelled"),
};
