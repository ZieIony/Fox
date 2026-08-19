#include "EnemyCharacter.h"

#include <EnemyAIComponent.h>
#include <AbilitySystemComponent.h>

void AEnemyCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

AEnemyCharacter::AEnemyCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	AIComponent = CreateDefaultSubobject<UEnemyAIComponent>(TEXT("Enemy AI"));

	SetGenericTeamId(ENEMY_TEAM_ID);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}
