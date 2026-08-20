#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

UCLASS()
class FOX_API UInteractionWidget: public UUserWidget {
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
};
