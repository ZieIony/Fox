#include "HeatSource.h"

AHeatSource::AHeatSource() {
	PrimaryActorTick.bCanEverTick = true;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
	InteractionComponent->SetupAttachment(RootComponent);

	HeatSourceComponent = CreateDefaultSubobject<UHeatSourceComponent>(TEXT("HeatSource"));
	HeatSourceComponent->SetupAttachment(InteractionComponent);
}

void AHeatSource::BeginPlay() {
	Super::BeginPlay();
}

void AHeatSource::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
