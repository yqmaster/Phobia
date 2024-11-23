#include "Component/Interaction/InteractionPlayerComponent.h"

#include "Component/Interaction/InteractionItemComponent.h"

UInteractionPlayerComponent::UInteractionPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionPlayerComponent::SetCurrentInteractionItem(UInteractionItemComponent* InInteractionItem)
{
	ensureAlwaysMsgf(IsValid(InInteractionItem), TEXT("SetCurrentInteractionItem for [%s] in [%s] is invalid"), *GetName(), *GetOwner()->GetName());
	CurrentInteractionItem = InInteractionItem;
}

void UInteractionPlayerComponent::ClearCurrentInteractionItem()
{
	CurrentInteractionItem = nullptr;
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

void UInteractionPlayerComponent::TriggerInteractionByClick(const EInteractionRoleType RoleType) const
{
	if (IsValid(CurrentInteractionItem))
	{
		CurrentInteractionItem->TakeInteractionByClick(GetOwner(), RoleType);
	}
}

void UInteractionPlayerComponent::TriggerInteractionByPress(const EInteractionRoleType RoleType, const bool IsStart)
{
	if (IsStart)
	{
		if (IsValid(CurrentInteractionItem))
		{
			InteractionCachedItemMap.Add(RoleType, CurrentInteractionItem);
			CurrentInteractionItem->TakeInteractionByPress(GetOwner(), RoleType, IsStart);
		}
		else
		{
			ensureAlwaysMsgf(false, TEXT("TriggerInteractionByPress on Start for [%s] in [%s] is invalid"), *GetName(), *GetOwner()->GetName());
		}
	}
	else
	{
		if (const TObjectPtr<UInteractionItemComponent> CachedItem = *InteractionCachedItemMap.Find(RoleType))
		{
			InteractionCachedItemMap.Remove(RoleType);

			if (IsValid(CachedItem))
			{
				CachedItem->TakeInteractionByPress(GetOwner(), RoleType, IsStart);
			}
		}
		else
		{
			ensureAlwaysMsgf(false, TEXT("TriggerInteractionByPress on End for [%s] in [%s] is invalid"), *GetName(), *GetOwner()->GetName());
		}
	}
}
