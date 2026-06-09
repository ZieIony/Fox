#include "HeatSubsystem.h"

void UHeatSubsystem::Tick(float DeltaTime) {
	for (auto item : heatSources) {
		item->UpdateSize(DeltaTime);
	}
}
