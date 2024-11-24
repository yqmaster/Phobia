#include "Component/Interaction/InteractionPlayerComponent.h"

#include "Component/Interaction/InteractionItemComponent.h"
#include "Component/Interaction/InteractionTypeDefine.h"

UInteractionPlayerComponent::UInteractionPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionPlayerComponent::SetCurrentInteractionItem(const EInteractionRoleType InRoleType, UInteractionItemComponent* InInteractionItem)
{
	ensureAlwaysMsgf(IsValid(InInteractionItem), TEXT("SetCurrentInteractionItem for [%s] in [%s] is invalid"), *GetName(), *GetOwner()->GetName());
	UE_LOG(LogTemp, Log, TEXT("Item [%s] is SetCurrentInteractionItem at role [%s]"), *InInteractionItem->GetName(), *UInteractionFunctionLibrary::EInteractionRoleTypeToString(InRoleType));
	InteractionItemMap.Add(InRoleType, InInteractionItem);
}

void UInteractionPlayerComponent::ClearCurrentInteractionItem(const EInteractionRoleType InRoleType)
{
	ensureAlwaysMsgf(InteractionItemMap.Find(InRoleType), TEXT("ClearCurrentInteractionItem for [%s] in [%s] is invalid"), *GetName(), *GetOwner()->GetName());
	UE_LOG(LogTemp, Log, TEXT("Item [%s] is ClearCurrentInteractionItem at role [%s]"), *InteractionItemMap.Find(InRoleType)->GetName(), *UInteractionFunctionLibrary::EInteractionRoleTypeToString(InRoleType));
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
	// 可交互的列表中 是否有对应物体
	UInteractionItemComponent* InteractionItem = FindInItemMap(RoleType);
	// 已经在交互的列表中 是否有对应物体
	const UInteractionItemComponent* CachedInteractionItem = FindInCachedItemMap(RoleType);

	//  开始交互的时候，得在可交互列表，并且没有正在交互
	if (IsStart && InteractionItem && !CachedInteractionItem)
	{
		InteractionCachedItemMap.Add(RoleType, InteractionItem);
		InteractionItem->TakeInteractionByPress(GetOwner(), RoleType, IsStart);
		return;
	}

	// 结束交互的时候，得在缓存的已经在交互的列表中
	if (!IsStart && CachedInteractionItem)
	{
		InteractionCachedItemMap.Remove(RoleType);
		InteractionItem->TakeInteractionByPress(GetOwner(), RoleType, IsStart);
		return;
	}
}

UInteractionItemComponent* UInteractionPlayerComponent::FindInItemMap(const EInteractionRoleType RoleType) const
{
	if (const TObjectPtr<UInteractionItemComponent>* InteractionItemPtr = InteractionItemMap.Find(RoleType))
	{
		if (const TObjectPtr<UInteractionItemComponent> InteractionItem = *InteractionItemPtr)
		{
			return InteractionItem;
		}
	}

	return nullptr;
}

UInteractionItemComponent* UInteractionPlayerComponent::FindInCachedItemMap(const EInteractionRoleType RoleType) const
{
	if (const TObjectPtr<UInteractionItemComponent>* InteractionItemPtr = InteractionCachedItemMap.Find(RoleType))
	{
		if (const TObjectPtr<UInteractionItemComponent> InteractionItem = *InteractionItemPtr)
		{
			return InteractionItem;
		}
	}

	return nullptr;
}
