#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionComponent.h"
#include "HeatSourceComponent.h"

#include "HeatSource.generated.h"

UCLASS()
class FOX_API AHeatSource: public AActor {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	UHeatSourceComponent* HeatSourceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	UInteractionComponent* InteractionComponent;

	virtual void BeginPlay() override;

public:
	AHeatSource();

	virtual void Tick(float DeltaTime) override;
};
