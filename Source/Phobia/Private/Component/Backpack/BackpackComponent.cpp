#include "Component/Backpack/BackpackComponent.h"

#include "Character/PCharacterBase.h"
#include "Component/Backpack/BackpackInterface.h"

UBackpackComponent::UBackpackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBackpackComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 移除所有物品
	RemoveAllFromBackpack();

	Super::EndPlay(EndPlayReason);
}

bool UBackpackComponent::IsInBackpack(AActor* InItem) const
{
	return InItem && PackageItems.Contains(InItem);
}

bool UBackpackComponent::IsBackpackFull() const
{
	return PackageItems.Num() >= MaxSize;
}

AActor* UBackpackComponent::GetItemByIndex(const int32 InIndex) const
{
	if (PackageItems.IsValidIndex(InIndex))
	{
		return PackageItems[InIndex];
	}

	return nullptr;
}

void UBackpackComponent::AddToInfiniteBackpack(AActor* InItem)
{
	if (InItem && !InfinitePackageItems.Contains(InItem))
	{
		InfinitePackageItems.Add(InItem);
	}
}

bool UBackpackComponent::AddToBackpack(AActor* InItem)
{
	if (InItem && !IsBackpackFull() && !IsInBackpack(InItem))
	{
		// 添加到背包
		AddToBackpackInternal(InItem);
		// 刚拾取的拿在手上
		UnSetCurrentItemInternal();
		SetCurrentItemInternal(InItem);
		return true;
	}

	return false;
}

bool UBackpackComponent::RemoveCurrentFromBackpack()
{
	return RemoveFromBackpackByItem(GetCurrentItem());
}

bool UBackpackComponent::RemoveFromBackpackByIndex(const int32 InIndex)
{
	return RemoveFromBackpackByItem(GetItemByIndex(InIndex));
}

bool UBackpackComponent::RemoveFromBackpackByItem(AActor* InItem)
{
	if (IsInBackpack(InItem))
	{
		// 移除的是否是手上的
		const bool bIsCurrentItem = IsCurrentItem(InItem);
		const int32 CurrentIndex = GetCurrentIndex();
		// 如果拿在手上，就取消持有
		if (bIsCurrentItem)
		{
			UnSetCurrentItemInternal();
		}

		RemoveFromBackpackInternal(InItem);

		// 如果拿在手上，就设置下一个
		if (bIsCurrentItem)
		{
			const int32 NextIndex = FindNextIndex(CurrentIndex);
			SetCurrentItemInternal(GetItemByIndex(NextIndex));
		};
		return true;
	}

	return false;
}

void UBackpackComponent::RemoveAllFromBackpack()
{
	// 取消持有
	UnSetCurrentItemInternal();

	TArray<TObjectPtr<AActor>> PackageItemsCopy = PackageItems;
	for (TObjectPtr<AActor> Item : PackageItemsCopy)
	{
		RemoveFromBackpackInternal(Item);
	}

	PackageItemsCopy.Empty();
	PackageItems.Empty();
}

AActor* UBackpackComponent::GetCurrentItem() const
{
	return CurrentItem;
}

int32 UBackpackComponent::GetCurrentIndex() const
{
	return PackageItems.Find(CurrentItem);
}

bool UBackpackComponent::IsCurrentItem(AActor* InItem) const
{
	return InItem && InItem == CurrentItem;
}

void UBackpackComponent::SetCurrentItemInternal(AActor* NewItem)
{
	CurrentItem = NewItem;

	if (const TObjectPtr<AActor> InItem = CurrentItem)
	{
		// 通知物体各组件被拿在手中了
		ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
		for (UActorComponent* Component : InItem->GetComponentsByInterface(UBackpackInterface::StaticClass()))
		{
			IBackpackInterface::Execute_OnSetToHand(Component, InItem, OwnerCharacter);
		}
	}
}

void UBackpackComponent::UnSetCurrentItemInternal()
{
	if (const TObjectPtr<AActor> InItem = CurrentItem)
	{
		// 通知物体各组件被拿在手中了
		ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
		for (UActorComponent* Component : InItem->GetComponentsByInterface(UBackpackInterface::StaticClass()))
		{
			IBackpackInterface::Execute_OnUnSetFromHand(Component, InItem, OwnerCharacter);
		}
	}

	CurrentItem = nullptr;
}

int32 UBackpackComponent::FindPreviousIndex(const int32 InIndex) const
{
	if (PackageItems.IsEmpty())
	{
		return INDEX_NONE;
	}

	return (InIndex + 1 + PackageItems.Num()) % PackageItems.Num();
}

int32 UBackpackComponent::FindNextIndex(const int32 InIndex) const
{
	if (PackageItems.IsEmpty())
	{
		return INDEX_NONE;
	}

	return (InIndex + 1) % PackageItems.Num();
}

void UBackpackComponent::AddToBackpackInternal(AActor* InItem)
{
	PackageItems.Add(InItem);

	// TODO 后面这里要写完善的
	// InItem->SetActorLocation(UNTOUCHABLE_LOCATION, false, nullptr, ETeleportType::ResetPhysics);

	// 通知物体各组件被加入到列表了
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (UActorComponent* Component : InItem->GetComponentsByInterface(UBackpackInterface::StaticClass()))
	{
		IBackpackInterface::Execute_OnAddToBackpack(Component, InItem, OwnerCharacter);
	}
}

void UBackpackComponent::RemoveFromBackpackInternal(AActor* InItem)
{
	// TODO 后面这里要写完善的
	// InItem->SetActorLocation(OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * 100, false, nullptr, ETeleportType::ResetPhysics);

	// 通知物体各组件被移除了
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (UActorComponent* Component : InItem->GetComponentsByInterface(UBackpackInterface::StaticClass()))
	{
		IBackpackInterface::Execute_OnRemoveFromBackpack(Component, InItem, OwnerCharacter);
	}

	PackageItems.Remove(InItem);
}
