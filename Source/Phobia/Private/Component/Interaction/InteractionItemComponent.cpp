#include "Component/Interaction/InteractionItemComponent.h"

#include "Component/Interaction/InteractionAbilityInfo.h"

UInteractionItemComponent::UInteractionItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	const AActor* OwnerActor = GetOwner();
	for (UInteractionAbilityInfo* AbilityInfo : AbilityInfos)
	{
		if (AbilityInfo)
		{
			AbilityInfo->InitAbilityInfo(OwnerActor, this);
		}
	}

	for (UInteractionAbilityInfo* AbilityInfo : TestAbilityInfos)
	{
		if (AbilityInfo)
		{
			AbilityInfo->InitAbilityInfo(OwnerActor, this);
		}
	}
}

void UInteractionItemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	const AActor* OwnerActor = GetOwner();
	for (UInteractionAbilityInfo* AbilityInfo : TestAbilityInfos)
	{
		if (AbilityInfo)
		{
			AbilityInfo->UnInitAbilityInfo(OwnerActor, this);
		}
	}

	for (UInteractionAbilityInfo* AbilityInfo : AbilityInfos)
	{
		if (AbilityInfo)
		{
			AbilityInfo->UnInitAbilityInfo(OwnerActor, this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UInteractionItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionItemComponent::InteractInScene(ETriggerEvent InTriggerEvent)
{
	if (OnInteractOnScene.IsBound())
	{
		OnInteractOnScene.Broadcast(InTriggerEvent);
	}
}
