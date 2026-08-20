#include "BasicAttributeSet.h"
#include <Net/UnrealNetwork.h>

UBasicAttributeSet::UBasicAttributeSet() {
	Stamina = 100.0f;
	MaxStamina = 100.0f;
}

void UBasicAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}
