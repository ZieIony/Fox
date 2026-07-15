#include "BTTaskPatrolPath.h"
#include "PatrolPath.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <EnemyAIComponent.h>

EPatrolDirection UBTTaskPatrolPath::ReversePatrolDirectionIfNeeded(UBlackboardComponent* blackboard, EPatrolDirection direction) {
	if (!ReversePatrolDirectionAtCompletion)
		return direction;

	auto newDirection = [direction] {
		if (direction == EPatrolDirection::Forward) {
			return EPatrolDirection::Backward;
		} else {
			return EPatrolDirection::Forward;
		}
	}();
	blackboard->SetValueAsEnum(CurrentPatrolDirectionKey.SelectedKeyName, (uint8)newDirection);
	return newDirection;
}

void UBTTaskPatrolPath::MoveToNextPoint(
	UBlackboardComponent* blackboard,
	APatrolPath* patrolPath,
	int currentPatrolPointIndex,
	EPatrolDirection currentPatrolDirection
) {
	auto nextPointIndex = patrolPath->GetNextPointIndex(currentPatrolPointIndex, currentPatrolDirection);
	blackboard->SetValueAsInt(CurrentPatrolPointIndexKey.SelectedKeyName, nextPointIndex);
}

EBTNodeResult::Type UBTTaskPatrolPath::ProcessStep(
	APatrolPath* patrolPath,
	UBlackboardComponent* blackboard,
	int currentPatrolPointIndex
) {
	auto currentPatrolDirection = (EPatrolDirection)blackboard->GetValueAsEnum(CurrentPatrolDirectionKey.SelectedKeyName);
	if (patrolMode == EPatrolMode::Step) {
		if (patrolPath->IsLastPointIndex(currentPatrolPointIndex, currentPatrolDirection))
			currentPatrolDirection = ReversePatrolDirectionIfNeeded(blackboard, currentPatrolDirection);
		MoveToNextPoint(blackboard, patrolPath, currentPatrolPointIndex, currentPatrolDirection);
		return EBTNodeResult::Succeeded;
	} else {
		if (patrolPath->IsLastPointIndex(currentPatrolPointIndex, currentPatrolDirection)) {
			currentPatrolDirection = ReversePatrolDirectionIfNeeded(blackboard, currentPatrolDirection);
			MoveToNextPoint(blackboard, patrolPath, currentPatrolPointIndex, currentPatrolDirection);
			return EBTNodeResult::Succeeded;
		} else {
			MoveToNextPoint(blackboard, patrolPath, currentPatrolPointIndex, currentPatrolDirection);
			return EBTNodeResult::InProgress;
		}
	}
}

EBTNodeResult::Type UBTTaskPatrolPath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto enemyAIComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UEnemyAIComponent>();
	if (enemyAIComponent && enemyAIComponent->PatrolPath == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("PatrolPath is null"));
		return EBTNodeResult::Failed;
	} else {
		auto patrolPath = enemyAIComponent->PatrolPath;
		auto blackboard = OwnerComp.GetBlackboardComponent();
		auto currentPatrolPointIndex = blackboard->GetValueAsInt(CurrentPatrolPointIndexKey.SelectedKeyName);
		auto pointLocation = patrolPath->GetPointLocation(currentPatrolPointIndex);

		auto aiController = Cast<AAIController>(OwnerComp.GetAIOwner());
		auto result = aiController->MoveToLocation(pointLocation, AcceptableRadius, false, true, true, true);
		if (result == EPathFollowingRequestResult::Type::Failed) {
			return EBTNodeResult::Failed;
		} else if (result == EPathFollowingRequestResult::Type::AlreadyAtGoal) {
			return ProcessStep(patrolPath.Get(), blackboard, currentPatrolPointIndex);
		} else {
			return EBTNodeResult::InProgress;
		}
	}
}

EBTNodeResult::Type UBTTaskPatrolPath::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto aiController = OwnerComp.GetAIOwner();
	aiController->StopMovement();
	return EBTNodeResult::Aborted;
}

void UBTTaskPatrolPath::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	auto enemyAIComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UEnemyAIComponent>();
	if (enemyAIComponent && enemyAIComponent->PatrolPath == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("PatrolPath is null"));
	} else {
		auto patrolPath = enemyAIComponent->PatrolPath;
		auto blackboard = OwnerComp.GetBlackboardComponent();
		auto currentPatrolPointIndex = blackboard->GetValueAsInt(CurrentPatrolPointIndexKey.SelectedKeyName);
		auto pointLocation = patrolPath->GetPointLocation(currentPatrolPointIndex);

		auto actorLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		float distSquared = FVector::DistSquared(pointLocation, actorLocation);
		if (distSquared <= FMath::Square(AcceptableRadius)) {
			if (ProcessStep(patrolPath.Get(), blackboard, currentPatrolPointIndex) == EBTNodeResult::Succeeded) {
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			} else {
				auto aiController = Cast<AAIController>(OwnerComp.GetAIOwner());
				auto result = aiController->MoveToLocation(pointLocation, AcceptableRadius, false, true, true, true);
				if (result == EPathFollowingRequestResult::Type::Failed) {
					FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				} else if (result == EPathFollowingRequestResult::Type::AlreadyAtGoal) {
					FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				}
			}
		} else {
			UE_LOG(LogTemp, Error, TEXT("Current distance: %f"), std::sqrt(distSquared));
		}
	}
}
