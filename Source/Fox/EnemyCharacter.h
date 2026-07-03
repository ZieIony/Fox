#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "EnemyCharacter.generated.h"

UCLASS()
class FOX_API AEnemyCharacter: public ACharacter {
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ChasePlayer() {
		auto playerController = GetWorld()->GetFirstPlayerController();
	}

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
