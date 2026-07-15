#pragma once

#include "CoreMinimal.h"
#include "EnemyAIState.generated.h"

UENUM(BlueprintType)
enum class EEnemyAIState: uint8 {
	Idle UMETA(DisplayName = "Idle"),
	Attacking UMETA(DisplayName = "Attacking"),
	Patrolling UMETA(DisplayName = "Patrolling"),
	Chasing UMETA(DisplayName = "Chasing"),
	Investigating UMETA(DisplayName = "Investigating"),
	Stunned UMETA(DisplayName = "Stunned"),
	Dead UMETA(DisplayName = "Dead")
};
