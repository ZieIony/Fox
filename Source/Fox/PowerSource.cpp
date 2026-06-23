#include "PowerSource.h"
#include "HeatSubsystem.h"
#include "FoxGameplayTagManager.h"

static FAutoConsoleCommand StartPowerSource(
	TEXT("StartPowerSource"),
	TEXT("StartPowerSource command"),
	FConsoleCommandDelegate::CreateLambda([]() {
	FWorldContext* worldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
	auto heatSubsystem = worldContext->World()->GetSubsystem<UHeatSubsystem>();
	if (heatSubsystem) {
		auto powerSource = heatSubsystem->GetFirstPowerSource(EPowerSourceType::Red);
		if (powerSource)
			powerSource->StartPowerSource();
	}
})
);

static FAutoConsoleCommand StopPowerSource(
	TEXT("StopPowerSource"),
	TEXT("StopPowerSource command"),
	FConsoleCommandDelegate::CreateLambda([]() {
	FWorldContext* worldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
	auto heatSubsystem = worldContext->World()->GetSubsystem<UHeatSubsystem>();
	if (heatSubsystem) {
		auto powerSource = heatSubsystem->GetFirstPowerSource(EPowerSourceType::Red);
		if (powerSource)
			powerSource->StopPowerSource();
	}
})
);

void APowerSource::BeginPlay() {
	Super::BeginPlay();

	UHeatSubsystem* heatSubsystem = GetWorld()->GetSubsystem<UHeatSubsystem>();
	if (!heatSubsystem) {
		// TODO: log error
		return;
	}

	heatSubsystem->ManagePowerSource(this);
}

void APowerSource::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	UHeatSubsystem* heatSubsystem = GetWorld()->GetSubsystem<UHeatSubsystem>();
	if (!heatSubsystem) {
		// TODO: log error
		return;
	}

	heatSubsystem->RemovePowerSource(this);
}

APowerSource::APowerSource() {
	PrimaryActorTick.bCanEverTick = true;
}
