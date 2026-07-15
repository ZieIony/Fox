#include "BTDecoratorHasPatrolPath.h"
#include <BehaviorTree/BehaviorTreeComponent.h>
#include "EnemyAIComponent.h"

bool UBTDecoratorHasPatrolPath::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	auto actor = OwnerComp.GetAIOwner()->GetPawn();
	if (!actor)
		return false;
	auto aiComponent = actor->FindComponentByClass<UEnemyAIComponent>();
	if (!aiComponent)
		return false;
	return aiComponent->PatrolPath != nullptr;
}
