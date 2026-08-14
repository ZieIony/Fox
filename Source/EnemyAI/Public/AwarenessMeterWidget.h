#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include <Components/ProgressBar.h>

#include "AwarenessMeterWidget.generated.h"

UCLASS()
class ENEMYAI_API UAwarenessMeterWidget: public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* ProgressBar;

	UFUNCTION(BlueprintCallable)
	void SetAwarenessLevel(float AwarenessLevel);

	UFUNCTION(BlueprintCallable)
	void SetAlerted(bool Alerted);

	UFUNCTION(BlueprintCallable)
	void SetAngle(float angle);

	virtual void NativeConstruct() override;
};
