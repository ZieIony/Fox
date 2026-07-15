#pragma once

#include "CoreMinimal.h"
#include "PatrolMode.generated.h"

UENUM(BlueprintType)
enum class EPatrolMode:uint8 {
	Step UMETA(DisplayName = "Patrol one step"),
	Path UMETA(DisplayName = "Patrol entire path")
};
