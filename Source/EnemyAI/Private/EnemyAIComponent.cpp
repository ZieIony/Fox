#include "EnemyAIComponent.h"

#include <GameFramework/Character.h>

AEnemyAIController* UEnemyAIComponent::GetAIController() const {
	auto character = Cast<ACharacter>(GetOwner());
	if (IsValid(character))
		return Cast<AEnemyAIController>(character->GetController());
	return nullptr;
}
