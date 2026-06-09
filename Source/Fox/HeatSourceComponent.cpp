#include "HeatSourceComponent.h"
#include "HeatSubsystem.h"

UHeatSourceComponent::UHeatSourceComponent() {
	PrimaryComponentTick.bCanEverTick = false;
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetCastShadow(false);
	SetRenderInMainPass(false);
	SetRenderInDepthPass(false);
	bUseAsOccluder = false;
	bReceivesDecals = false;
}

void UHeatSourceComponent::BeginPlay() {
	Super::BeginPlay();

	UHeatSubsystem* heatSubsystem = GetWorld()->GetSubsystem<UHeatSubsystem>();
	if (!heatSubsystem) {
		// TODO: log error
		return;
	}

	heatSubsystem->ManageHeatSource(this);

	SetActive(true);
}

void UHeatSourceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	UHeatSubsystem* heatSubsystem = GetWorld()->GetSubsystem<UHeatSubsystem>();
	if (!heatSubsystem) {
		// TODO: log error
		return;
	}

	heatSubsystem->RemoveHeatSource(this);
}
