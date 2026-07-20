#include "EnemyAIComponent.h"

#include <GameFramework/Character.h>

void UEnemyAIComponent::BeginPlay() {
	if (IsValid(AwarenessMeterWidgetClass)) {
		AwarenessMeterWidget = CreateWidget<UAwarenessMeterWidget>(GetWorld(), AwarenessMeterWidgetClass);
		AwarenessMeterWidget->AddToViewport();
	} else {
		UE_LOG(LogTemp, Error, TEXT("AwarenessMeterWidgetClass is null"));
	}

	auto character = Cast<ACharacter>(GetOwner());
	EnemyAIController = Cast<AEnemyAIController>(character->GetController());
	if (IsValid(EnemyAIController)) {
		EnemyAIController->AwarenessMeterWidget = AwarenessMeterWidget;
	} else {
		UE_LOG(LogTemp, Error, TEXT("AwarenessMeterWidget is null"));
	}
}
