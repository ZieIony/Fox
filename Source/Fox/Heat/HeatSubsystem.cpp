#include "HeatSubsystem.h"

void UHeatSubsystem::PowerSourceOnWorkingChanged(APowerSource* powerSource, bool working) {
	for (auto& heatSource : heatSources) {
		if (heatSource->PowerSource == powerSource) {
			if (!working)
				heatSource->StopHeatSource();
		}
	}
}

void UHeatSubsystem::Tick(float DeltaTime) {
	for (auto item : heatSources) {
		item->UpdateSize(DeltaTime);
	}
}
