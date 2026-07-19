#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <InputAction.h>
#include <InputMappingContext.h>
#include <Runtime/AIModule/Classes/GenericTeamAgentInterface.h>

#include "FoxCharacter.generated.h"

UCLASS()
class FOX_API AFoxCharacter: public ACharacter, public IGenericTeamAgentInterface {
	GENERATED_BODY()

private:
	FGenericTeamId teamId;

public:
	// camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	// input
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* LookAction;

	AFoxCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override {
		teamId = NewTeamID;
	}

	virtual FGenericTeamId GetGenericTeamId() const override { return teamId; }

	void Move(const FInputActionValue& value);

	void JumpStarted(const FInputActionValue& value);

	void JumpEnded(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void MakeLittleNoise(float MaxRange);
};
