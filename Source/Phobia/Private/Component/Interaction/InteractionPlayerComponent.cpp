#include "Component/Interaction/InteractionPlayerComponent.h"

#include "Component/Interaction/InteractionItemComponent.h"

UInteractionPlayerComponent::UInteractionPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionPlayerComponent::SetCurrentInteractionItem(const EInteractionRoleType InRoleType, UInteractionItemComponent* InInteractionItem)
{
	ensureAlwaysMsgf(IsValid(InInteractionItem), TEXT("SetCurrentInteractionItem for [%s] in [%s] is invalid"), *GetName(), *GetOwner()->GetName());
	InteractionItemMap.Add(InRoleType, InInteractionItem);
}

void UInteractionPlayerComponent::ClearCurrentInteractionItem(const EInteractionRoleType InRoleType)
{
	ensureAlwaysMsgf(InteractionItemMap.Find(InRoleType), TEXT("ClearCurrentInteractionItem for [%s] in [%s] is invalid"), *GetName(), *GetOwner()->GetName());
	InteractionItemMap.Remove(InRoleType);
}

void UInteractionPlayerComponent::TriggerInteractionByClick(const EInteractionRoleType RoleType) const
{
	if (const TObjectPtr<UInteractionItemComponent>* InteractionItemPtr = InteractionItemMap.Find(RoleType))
	{
		if (const TObjectPtr<UInteractionItemComponent> InteractionItem = *InteractionItemPtr)
		{
			InteractionItem->TakeInteractionByClick(GetOwner(), RoleType);
		}
	}
}

void UInteractionPlayerComponent::TriggerInteractionByPress(const EInteractionRoleType RoleType, const bool IsStart)
{
	if (IsStart)
	{
		if (const TObjectPtr<UInteractionItemComponent>* InteractionItemPtr = InteractionItemMap.Find(RoleType))
		{
			if (const TObjectPtr<UInteractionItemComponent> InteractionItem = *InteractionItemPtr)
			{
				InteractionCachedItemMap.Add(RoleType, InteractionItem);
				InteractionItem->TakeInteractionByPress(GetOwner(), RoleType, IsStart);
			}
		}
	}
	else
	{
		if (const TObjectPtr<UInteractionItemComponent>* InteractionItemPtr = InteractionCachedItemMap.Find(RoleType))
		{
			if (const TObjectPtr<UInteractionItemComponent> InteractionItem = *InteractionItemPtr)
			{
				InteractionCachedItemMap.Remove(RoleType);
				InteractionItem->TakeInteractionByPress(GetOwner(), RoleType, IsStart);
			}
		}
	}
}
