#pragma once

#include "CoreMinimal.h"
#include <AttributeSet.h>
#include <AbilitySystemComponent.h>

#include "BasicAttributeSet.generated.h"

UCLASS()
class FOX_API UBasicAttributeSet: public UAttributeSet {
	GENERATED_BODY()

public:
	UBasicAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Stamina);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData PrevValue) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Stamina, PrevValue);
	}

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxStamina);

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData PrevValue) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, MaxStamina, PrevValue);
	}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
