#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Heater.generated.h"

UCLASS()
class FOX_API AHeater: public AActor {
	GENERATED_BODY()

public:
	AHeater();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
