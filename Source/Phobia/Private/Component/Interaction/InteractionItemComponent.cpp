#include "Component/Interaction/InteractionItemComponent.h"

#include "Component/Interaction/InteractionAbilityDataAsset.h"
#include "Component/Interaction/InteractionAbilityInfo.h"

UInteractionItemComponent::UInteractionItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionItemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionAbilityAsset)
	{
		for (UInteractionAbilityInfo* AbilityInfo : InteractionAbilityAsset->GetAllAbilityInfos())
		{
			AbilityInfos.Add(AbilityInfo);
		}
	}

	AActor* OwnerActor = GetOwner();

	for (UInteractionAbilityInfo* AbilityInfo : AbilityInfos)
	{
		if (AbilityInfo)
		{
			AbilityInfo->InitAbilityInfo(OwnerActor, this);
		}
	}

	for (UInteractionAbilityInfo* AbilityInfo : AbilityInfos)
	{
		if (AbilityInfo)
		{
			AbilityInfo->ActiveAbilityInfo();
		}
	}
}

void UInteractionItemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AActor* OwnerActor = GetOwner();

	for (UInteractionAbilityInfo* AbilityInfo : AbilityInfos)
	{
		if (AbilityInfo)
		{
			AbilityInfo->DeActiveAbilityInfo();
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

void UInteractionItemComponent::TakeInteractionByClick(AActor* Taker, EInteractionRoleType RoleType) const
{
	OnInteractByClick.Broadcast(Taker, RoleType);
}

void UInteractionItemComponent::TakeInteractionByPress(AActor* Taker, EInteractionRoleType RoleType, bool IsStart) const
{
	OnInteractByPress.Broadcast(Taker, RoleType, IsStart);
}
