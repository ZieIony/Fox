#include "AwarenessMeterWidget.h"

void UAwarenessMeterWidget::SetProgress(float progress) {
	ProgressBar->SetPercent(progress);
}

UFUNCTION(BlueprintCallable)
void UAwarenessMeterWidget::SetAngle(float angle) {
	ProgressBar->SetRenderTransformAngle(angle);
}

