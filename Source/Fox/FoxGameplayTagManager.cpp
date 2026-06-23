#include "FoxGameplayTagManager.h"
#include "GameplayTagsManager.h"

FGameplayTag FFoxGameplayTagManager::PowerSourceType;

FGameplayTag FFoxGameplayTagManager::PowerSourceType_Red;
FGameplayTag FFoxGameplayTagManager::PowerSourceType_Blue;
FGameplayTag FFoxGameplayTagManager::PowerSourceType_Green;

void FFoxGameplayTagManager::Init() {
    PowerSourceType = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("PowerSourceType"), "Power source type");

    PowerSourceType_Red = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("PowerSourceType.Red"), "Red power source");
    PowerSourceType_Blue = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("PowerSourceType.Blue"), "Blue power source");
    PowerSourceType_Green = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("PowerSourceType.Green"), "Green power source");
}
