#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Runtime/AIModule/Classes/GenericTeamAgentInterface.h>
#include <AbilitySystemInterface.h>

#include "EnemyCharacter.generated.h"

UCLASS()
class FOX_API AEnemyCharacter: public ACharacter, public IGenericTeamAgentInterface, public IAbilitySystemInterface {
	GENERATED_BODY()

protected:
	virtual void PossessedBy(AController* NewController) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UEnemyAIComponent* AIComponent;

	// team id
private:
	static const inline FGenericTeamId ENEMY_TEAM_ID = 1;

	FGenericTeamId teamId;

public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override {
		teamId = NewTeamID;
	}

	virtual FGenericTeamId GetGenericTeamId() const override { return teamId; }

	// abilities
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	}

	AEnemyCharacter();
};
