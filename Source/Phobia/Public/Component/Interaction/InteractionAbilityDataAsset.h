#pragma once

#include "CoreMinimal.h"
#include "Component/Character/Backpack/BackpackComponent.h"
#include "Engine/DataAsset.h"
#include "Component/Interaction/InteractionTypeDefine.h"
#include "InteractionAbilityDataAsset.generated.h"

class USimpleAbilityConfigEventBase;
class USimpleAbilityConfigConditionBase;
class USimpleAbilityConfigOperatorBase;
class USimpleAbilitySkill;

// 可交互物品的可生效位置
UENUM(BlueprintType)
enum class EInteractionEffectPlaceType : uint8
{
	Scene UMETA(DisplayName = "场景"),
	Hand UMETA(DisplayName = "手上"),
};

/**
 * 
 */
UCLASS(Blueprintable)
class PHOBIA_API UInteractionAbilityDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// 外界调用，获取所有的 AbilityInfo
	UFUNCTION(BlueprintCallable)
	TArray<USimpleAbilitySkill*> GetAllAbilityInfos(AActor* InOwner) const;

private:
	// 收集拾取相关的信息
	void GetPickAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const;
	// 收集丢弃相关的信息
	void GetDropAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const;
	// 收集放置相关的信息
	void GetPutAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const;
	// 收集点击相关的信息
	void GetClickAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const;
	// 收集长按相关的信息-·	
	void GetPressAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const;

	// 根据 EffectPlaceType 获取 RoleType
	static EInteractionRoleType GetRoleTypeByEffectPlaceType(EInteractionEffectPlaceType InEffectPlaceType);
	// 将 EffectPlaceType 转换为字符串
	static FString EInteractionRoleTypeToString(const EInteractionEffectPlaceType InEffectPlaceType);

protected:
	// 拾取/丢弃/放置

	// 是否能被拾取
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否能拾取丢弃"))
	bool bCanBePick = false;

	// 是否能被拾取
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否添加到无限背包", EditCondition = "bCanBePick", EditConditionHides))
	bool bAddToInfiniteBackpack = false;

	// 拾取的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "拾取的额外效果", EditCondition = "bCanBePick", EditConditionHides), Instanced)
	TArray<TObjectPtr<USimpleAbilityConfigOperatorBase>> PickOperators;

	// 丢弃时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "丢弃的方式", EditCondition = "bCanBePick && !bAddToInfiniteBackpack", EditConditionHides))
	EDropType DropType = EDropType::None;

	// 是否能被放置
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否能被放置", EditCondition = "bCanBePick && !bAddToInfiniteBackpack", EditConditionHides))
	bool bCanBePut = false;

	// 放置的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "放置条件", EditCondition = "bCanBePick && bCanBePut && !bAddToInfiniteBackpack", EditConditionHides), Instanced)
	TArray<TObjectPtr<USimpleAbilityConfigConditionBase>> PutConditions;

	// 放置的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "放置的效果", EditCondition = "bCanBePick && bCanBePut && !bAddToInfiniteBackpack", EditConditionHides), Instanced)
	TArray<TObjectPtr<USimpleAbilityConfigOperatorBase>> PutOperators;

	// 点击

	// 是否能被点击
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "能否被点击"))
	bool bCanBeClick = false;

	// 点击前的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击条件", EditCondition = "bCanBeClick", EditConditionHides), Instanced)
	TArray<TObjectPtr<USimpleAbilityConfigConditionBase>> ClickConditions;

	// 点击时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击效果", EditCondition = "bCanBeClick", EditConditionHides), Instanced)
	TArray<TObjectPtr<USimpleAbilityConfigOperatorBase>> ClickOperators;

	// 点击可作用的地方
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击可作用的地方", EditCondition = "bCanBeClick", EditConditionHides))
	TArray<EInteractionEffectPlaceType> ClickEffectPlaceTypes;

	// 长按

	// 是否能被长按
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "能否被长按"))
	bool bCanBePress = false;

	// 长按前的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按条件", EditCondition = "bCanBePress", EditConditionHides), Instanced)
	TArray<TObjectPtr<USimpleAbilityConfigConditionBase>> PressConditions;

	// 长按时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按效果", EditCondition = "bCanBePress", EditConditionHides), Instanced)
	TArray<TObjectPtr<USimpleAbilityConfigOperatorBase>> PressOperators;

	// 长按可作用的地方
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按可作用的地方", EditCondition = "bCanBePress", EditConditionHides))
	TArray<EInteractionEffectPlaceType> PressEffectPlaceTypes;
};
