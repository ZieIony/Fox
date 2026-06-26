#include "InteractionComponent.h"

#include "FoxCharacter.h"

void UInteractionComponent::InteractionSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResults) {
	auto foxCharacter = Cast<AFoxCharacter>(OtherActor);
	if (foxCharacter)
		EnableInteraction((APlayerController*)foxCharacter->GetController());
}

void UInteractionComponent::InteractionSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	auto foxCharacter = Cast<AFoxCharacter>(OtherActor);
	if (foxCharacter)
		DisableInteraction((APlayerController*)foxCharacter->GetController());
}

void UInteractionComponent::BeginPlay() {
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::InteractionSphereOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::InteractionSphereOverlapEnd);

	DisableInteraction(nullptr);
}

UInteractionComponent::UInteractionComponent() {
	PrimaryComponentTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->SetupAttachment(this);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(this);
}

void UInteractionComponent::OnRegister() {
	Super::OnRegister();

	// TODO: BUGBUG: Work around the 'Template Mismatch during attachment. Attaching instanced component to template component.' problem.
	// Remove after Epic acknowledges and fixes this long-standing bug or provides guidance.
	// The constructor-initialized components, upon non-CDO instantiation/initialization, are getting CDO references for their attached parents, instead of instance references.
	// A work-around...
	//     - Use SetupAttachment(), per usual in the constructor to establish the parent-child relationship for CDOs.
	//     - Use AttachToComponent() to override those errant CDO references with instance references, in your USceneComponent::OnRegister() override.
	CollisionComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	WidgetComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
