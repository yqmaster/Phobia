#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Component/Interaction/InteractionTypeDefine.h"
#include "InteractionAbilityDataAsset.generated.h"

class UInteractionEvent_TriggerByInput;
class UInteractionEventBase;
class UInteractionOperatorBase;
class UInteractionConditionBase;
class UInteractionAbilityInfo;

// 可交互物品的可生效位置
UENUM(BlueprintType)
enum class EInteractionEffectPlaceType : uint8
{
	Scene UMETA(DisplayName = "场景"),
	Hand UMETA(DisplayName = "手上"),
};

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
UCLASS(Blueprintable)
class PHOBIA_API UInteractionAbilityDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<UInteractionAbilityInfo*> GetAllAbilityInfos();

private:
	void GetPickAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos);
	void GetDropAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos);
	void GetPutAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos);
	void GetClickAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos);
	void GetPressAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos);

	UInteractionAbilityInfo* CreateAbilityInfo(UInteractionEventBase* InEvent, const TArray<TObjectPtr<UInteractionConditionBase>>& InConditions, const TArray<TObjectPtr<UInteractionOperatorBase>>& InOperators);
	UInteractionAbilityInfo* CreateAbilityInfoWithCopy(const UInteractionEventBase* InEvent, const TArray<TObjectPtr<UInteractionConditionBase>>& InConditions, const TArray<TObjectPtr<UInteractionOperatorBase>>& InOperators);
	static UInteractionEvent_TriggerByInput* CreateTriggerByInputEvent(EInteractionEventType InTriggerType, EInteractionRoleType InRoleType);
	static EInteractionRoleType GetRoleTypeByEffectPlaceType(EInteractionEffectPlaceType InEffectPlaceType);

	template <typename InObjectType>
	TArray<TObjectPtr<InObjectType>> DuplicateArray(const TArray<TObjectPtr<InObjectType>>& InArray);

protected:
	// 拾取/丢弃/放置

	// 是否能被拾取
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否能拾取丢弃"))
	bool bCanBePick = false;

	// 拾取的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "拾取的额外效果", EditCondition = "bCanBePick", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> PickOperators;

	// 丢弃时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "丢弃的方式", EditCondition = "bCanBePick", EditConditionHides))
	EDropType DropType = EDropType::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否能被放置", EditCondition = "bCanBePick", EditConditionHides))
	bool bCanBePut = false;

	// 放置的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "放置条件", EditCondition = "bCanBePick && bCanBePut", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionConditionBase>> PutConditions;

	// 放置的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "放置的效果", EditCondition = "bCanBePick && bCanBePut", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> PutOperators;

	// 点击

	// 是否能被点击
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "能否被点击"))
	bool bCanBeClick = false;

	// 点击前的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击条件", EditCondition = "bCanBeClick", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionConditionBase>> ClickConditions;

	// 点击时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击效果", EditCondition = "bCanBeClick", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> ClickOperators;

	// 点击可作用的地方
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击可作用的地方", EditCondition = "bCanBeClick", EditConditionHides))
	TArray<EInteractionEffectPlaceType> ClickEffectPlaceTypes;

	// 长按

	// 是否能被长按
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "能否被长按"))
	bool bCanBePress = false;

	// 长按前的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按条件", EditCondition = "bCanBePress", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionConditionBase>> PressConditions;

	// 长按时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按效果", EditCondition = "bCanBePress", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> PressOperators;

	// 长按可作用的地方
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按可作用的地方", EditCondition = "bCanBePress", EditConditionHides))
	TArray<EInteractionEffectPlaceType> PressEffectPlaceTypes;
};

template <typename InObjectType>
TArray<TObjectPtr<InObjectType>> UInteractionAbilityDataAsset::DuplicateArray(const TArray<TObjectPtr<InObjectType>>& InArray)
{
	TArray<TObjectPtr<InObjectType>> NewArray;
	for (const InObjectType* OldObj : InArray)
	{
		NewArray.Add(DuplicateObject<InObjectType>(OldObj, this));
	}
	return NewArray;
}
