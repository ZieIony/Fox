#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagsClasses.h"

class FOX_API FFoxGameplayTagManager: public FNoncopyable {
public:
	static FGameplayTag PowerSourceType;

	static FGameplayTag PowerSourceType_Red;
	static FGameplayTag PowerSourceType_Blue;
	static FGameplayTag PowerSourceType_Green;

	static void Init();
};
