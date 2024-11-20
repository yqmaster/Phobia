#include "Component/Interaction/InteractionPlayerComponent.h"

UInteractionPlayerComponent::UInteractionPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInteractionPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UInteractionPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

