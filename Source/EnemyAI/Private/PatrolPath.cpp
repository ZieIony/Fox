#include "PatrolPath.h"
#include <Logging/LogMacros.h>
#include <Logging/LogVerbosity.h>

APatrolPath::APatrolPath() {
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(Spline);
}

int APatrolPath::GetFirstPointIndex(EPatrolDirection direction) {
	if (direction == EPatrolDirection::Forward) {
		return 0;
	} else {
		return Spline->GetNumberOfSplinePoints() - 1;
	}
}

int APatrolPath::GetNextPointIndex(int currentPointIndex, EPatrolDirection direction) {
	auto splinePoints = Spline->GetNumberOfSplinePoints();
	if (direction == EPatrolDirection::Forward) {
		return (currentPointIndex + 1 + splinePoints) % splinePoints;
	} else {
		return (currentPointIndex - 1 + splinePoints) % splinePoints;
	}
}

bool APatrolPath::IsLastPointIndex(int pointIndex, EPatrolDirection direction) {
	auto splinePoints = Spline->GetNumberOfSplinePoints();
	if (direction == EPatrolDirection::Forward) {
		return (pointIndex + splinePoints) % splinePoints == splinePoints - 1;
	} else {
		return (pointIndex + splinePoints) % splinePoints == 0;
	}
}

FVector APatrolPath::GetPointLocation(int pointIndex) {
	auto splinePoints = Spline->GetNumberOfSplinePoints();
	return Spline->GetLocationAtSplinePoint(
		(pointIndex + splinePoints) % splinePoints,
		ESplineCoordinateSpace::World
	);
}
