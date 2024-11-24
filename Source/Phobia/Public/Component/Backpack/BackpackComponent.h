#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"

// 可拾取物品的丢弃类型
UENUM(BlueprintType)
enum class EDropType : uint8
{
	None UMETA(DisplayName = "空，无意义"),
	Trough UMETA(DisplayName = "抛物线丢弃"),
	Drop UMETA(DisplayName = "垂直丢弃"),
};

/**
 * 
 */
UCLASS(Blueprintable, Abstract, ClassGroup = (Backpack))
class PHOBIA_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBackpackComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// 添加相关

	// 是否在背包中
	UFUNCTION(BlueprintCallable)
	bool IsInBackpack(AActor* InItem) const;

	// 背包是否已满
	UFUNCTION(BlueprintCallable)
	bool IsBackpackFull() const;

	// 通过索引获取物品
	UFUNCTION(BlueprintCallable)
	AActor* GetItemByIndex(int32 InIndex) const;

	// 添加到无限背包
	UFUNCTION(BlueprintCallable)
	void AddToInfiniteBackpack(AActor* InItem);

	// 添加到背包
	UFUNCTION(BlueprintCallable)
	bool AddToBackpack(AActor* InItem);

	// 移除当前物品
	UFUNCTION(BlueprintCallable)
	bool RemoveCurrentFromBackpack();

	// 通过索引从背包中移除
	UFUNCTION(BlueprintCallable)
	bool RemoveFromBackpackByIndex(int32 InIndex);

	// 通过物品从背包中移除
	UFUNCTION(BlueprintCallable)
	bool RemoveFromBackpackByItem(AActor* InItem);

	// 移除所有物品
	UFUNCTION(BlueprintCallable)
	void RemoveAllFromBackpack();

	// 持有相关

	// 获取当前物品
	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentItem() const;

	// 获取当前物品索引
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentIndex() const;

	// 是否是当前物品
	UFUNCTION(BlueprintCallable)
	bool IsCurrentItem(AActor* InItem) const;

private:
	// 设置当前物品
	void SetCurrentItemInternal(AActor* NewItem);
	// 移除当前物品
	void UnSetCurrentItemInternal();
	int32 FindPreviousIndex(const int32 InIndex) const;
	int32 FindNextIndex(const int32 InIndex) const;
	// 添加到背包
	void AddToBackpackInternal(AActor* InItem);
	// 从背包中移除
	void RemoveFromBackpackInternal(AActor* InItem);

protected:
	// 背包最大容量
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Backpack")
	int32 MaxSize = 3;

private:
	UPROPERTY(Transient)
	TObjectPtr<AActor> CurrentItem;

	UPROPERTY(Transient)
	TArray<TObjectPtr<AActor>> PackageItems;

	UPROPERTY(Transient)
	TArray<TObjectPtr<AActor>> InfinitePackageItems;
};
