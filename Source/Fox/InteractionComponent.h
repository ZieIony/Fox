#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <Components/SphereComponent.h>
#include <Components/WidgetComponent.h>

#include "InteractionComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FOX_API UInteractionComponent: public USceneComponent {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	UWidgetComponent* WidgetComponent;

	UFUNCTION()
	void InteractionSphereOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool FromSweep,
		const FHitResult& SweepResults
	);

	UFUNCTION()
	void InteractionSphereOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	virtual void BeginPlay() override;

public:
	UInteractionComponent();

	void EnableInteraction(APlayerController* PlayerController) {
		GetOwner()->EnableInput(PlayerController);
		WidgetComponent->SetVisibility(true);
	}

	void DisableInteraction(APlayerController* PlayerController) {
		GetOwner()->DisableInput(PlayerController);
		WidgetComponent->SetVisibility(false);
	}

	virtual void OnRegister() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
