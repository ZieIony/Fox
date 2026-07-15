#pragma once

#include "CoreMinimal.h"
#include "PatrolDirection.generated.h"

UENUM(BlueprintType)
enum class EPatrolDirection:uint8 {
	Forward, Backward
};
