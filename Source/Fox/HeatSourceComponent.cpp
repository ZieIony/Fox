#include "HeatSourceComponent.h"

#include "HeatSubsystem.h"
#include "PowerSource.h"

static FAutoConsoleCommand StartHeatSource(
	TEXT("StartHeatSource"),
	TEXT("StartHeatSource command"),
	FConsoleCommandDelegate::CreateLambda([]() {
	FWorldContext* worldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
	auto heatSubsystem = worldContext->World()->GetSubsystem<UHeatSubsystem>();
	if (heatSubsystem) {
		auto heatSource = heatSubsystem->GetFirstHeatSource(EPowerSourceType::Red);
		if (heatSource)
			heatSource->StartHeatSource();
	}
})
);

static FAutoConsoleCommand StopHeatSource(
	TEXT("StopHeatSource"),
	TEXT("StopHeatSource command"),
	FConsoleCommandDelegate::CreateLambda([]() {
	FWorldContext* worldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
	auto heatSubsystem = worldContext->World()->GetSubsystem<UHeatSubsystem>();
	if (heatSubsystem) {
		auto heatSource = heatSubsystem->GetFirstHeatSource(EPowerSourceType::Red);
		if (heatSource)
			heatSource->StopHeatSource();
	}
})
);

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

bool UHeatSourceComponent::StartHeatSource() {
	if (!PowerSource)
		return false;
	if (PowerSource->PowerSourceState != EPowerSourceState::Working)
		return false;
	if (HeatSourceState == EHeatSourceState::Broken || HeatSourceState == EHeatSourceState::Working)
		return false;
	HeatSourceState = EHeatSourceState::Working;
	return true;
}

bool UHeatSourceComponent::StartHeatSource(APowerSource* powerSource) {
	this->PowerSource = powerSource;
	return StartHeatSource();
}
