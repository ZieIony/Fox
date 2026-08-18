#pragma once

#include "CoreMinimal.h"
#include "PerceptionState.generated.h"

UENUM(BlueprintType)
enum class EPerceptionState: uint8 {
	Idle UMETA(DisplayName = "Idle"),
	Suspicious UMETA(DisplayName = "Suspicious"),
	Alerted UMETA(DisplayName = "Alerted"),
	Engaged UMETA(DisplayName = "Engaged")
};
