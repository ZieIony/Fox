#include "FoxCharacter.h"

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

AFoxCharacter::AFoxCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AFoxCharacter::BeginPlay() {
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(Controller);
	if (playerController) {
		auto* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			playerController->GetLocalPlayer()
		);
		if (subsystem) {
			subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AFoxCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AFoxCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent) {
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFoxCharacter::Move);

		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AFoxCharacter::JumpStarted);
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFoxCharacter::JumpEnded);
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &AFoxCharacter::JumpEnded);
	} else {
		throw std::exception("enhancedInputComponent is null");
	}
}

void AFoxCharacter::Move(const FInputActionValue& value) {
	FVector2D moveActionValue = value.Get<FVector2D>();
	FVector dir = { moveActionValue.Y, moveActionValue.X, 0 };
	AddMovementInput(dir);
}

void AFoxCharacter::JumpStarted(const FInputActionValue& value) {
	Jump();
}

void AFoxCharacter::JumpEnded(const FInputActionValue& value) {
	StopJumping();
}
