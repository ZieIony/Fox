#include "EnemyCharacter.h"

#include <EnemyAIComponent.h>

AEnemyCharacter::AEnemyCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	AIComponent = CreateDefaultSubobject<UEnemyAIComponent>(TEXT("AI"));
}
