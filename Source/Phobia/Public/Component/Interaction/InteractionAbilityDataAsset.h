#pragma once

#include "CoreMinimal.h"
#include "InteractionItemComponent.h"
#include "Engine/DataAsset.h"
#include "InteractionAbilityDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PHOBIA_API UInteractionAbilityDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
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
	TArray<EInteractionRoleType> ClickRoleType;

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
	TArray<EInteractionRoleType> PressRoleType;

	// TODO 测试用, 回头删了
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	TArray<UInteractionAbilityInfo*> TestAbilityInfos;
};
