#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <InputAction.h>
#include <InputMappingContext.h>
#include <Runtime/AIModule/Classes/GenericTeamAgentInterface.h>
#include <AbilitySystemInterface.h>

#include "FoxCharacter.generated.h"

UCLASS()
class FOX_API AFoxCharacter: public ACharacter, public IGenericTeamAgentInterface, public IAbilitySystemInterface {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;

public:
	AFoxCharacter();

	// camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	// input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	void Move(const FInputActionValue& value);

	void JumpStarted(const FInputActionValue& value);

	void JumpEnded(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// team id
private:
	static const inline FGenericTeamId PLAYER_TEAM_ID = 0;

	FGenericTeamId teamId;

public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override {
		teamId = NewTeamID;
	}

	virtual FGenericTeamId GetGenericTeamId() const override { return teamId; }

	// abilities
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	}

	UFUNCTION(BlueprintCallable)
	void MakeLittleNoise(float MaxRange);

	virtual void Tick(float DeltaTime) override;
};
