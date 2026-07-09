#pragma once

#include "CoreMinimal.h"
#include "EnemyAIState.generated.h"

UENUM(BlueprintType)
enum class EEnemyAIState: uint8 {
	Idle UMETA(DisplayName = "Idle"),
	Attacking UMETA(DisplayName = "Attacking")
};
