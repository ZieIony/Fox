#include "Heater.h"

AHeater::AHeater() {
	PrimaryActorTick.bCanEverTick = true;
}

void AHeater::BeginPlay() {
	Super::BeginPlay();
}

void AHeater::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
