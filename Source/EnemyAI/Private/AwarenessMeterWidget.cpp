#include "AwarenessMeterWidget.h"

void UAwarenessMeterWidget::SetAwarenessLevel(float AwarenessLevel) {
	ProgressBar->SetPercent(AwarenessLevel);
}

void UAwarenessMeterWidget::SetAlerted(bool Alerted) {
	//ProgressBar->SetTint();
}

UFUNCTION(BlueprintCallable)
void UAwarenessMeterWidget::SetAngle(float angle) {
	ProgressBar->SetRenderTransformAngle(angle);
}

void UAwarenessMeterWidget::NativeConstruct() {
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Collapsed);
}

