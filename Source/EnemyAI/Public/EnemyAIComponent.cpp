#include "EnemyAIComponent.h"

#include <GameFramework/Character.h>

void UEnemyAIComponent::OnRegister() {
	Super::OnRegister();

	auto character = Cast<ACharacter>(GetOwner());
	if (IsValid(character))
		AIController = Cast<AEnemyAIController>(character->GetController());
}
