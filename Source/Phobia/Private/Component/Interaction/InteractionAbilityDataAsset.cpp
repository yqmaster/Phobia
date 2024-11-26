#include "Component/Interaction/InteractionAbilityDataAsset.h"

#include "SimpleAbilitySkill.h"
#include "Component/Interaction/Events/InteractionEvent_TriggerByInput.h"
#include "Component/Interaction/Operators/InteractionOperator_DropItem.h"
#include "Component/Interaction/Operators/InteractionOperator_PickItem.h"

TArray<USimpleAbilitySkill*> UInteractionAbilityDataAsset::GetAllAbilityInfos(AActor* InOwner) const
{
	TArray<USimpleAbilitySkill*> AbilityInfos;

	// 拾取相关
	GetPickAbilityInfo(InOwner, AbilityInfos);
	// 丢弃相关
	GetDropAbilityInfo(InOwner, AbilityInfos);
	// 放置相关
	GetPutAbilityInfo(InOwner, AbilityInfos);
	// 点击相关
	GetClickAbilityInfo(InOwner, AbilityInfos);
	// 长按相关
	GetPressAbilityInfo(InOwner, AbilityInfos);

	return AbilityInfos;
}

void UInteractionAbilityDataAsset::GetPickAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const
{
	if (bCanBePick)
	{
		// 触发类型: 点击, 作用类型: 拾取
		const UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Click, EInteractionRoleType::Pick);
		// TODO 这里拾取应该需要额外的条件检查，例如手上是否拿满了
		const TArray<USimpleAbilityConfigConditionBase*> PickConditions;
		TArray<TObjectPtr<USimpleAbilityConfigOperatorBase>> InPickOperators = PickOperators;

		InPickOperators.Add(UInteractionOperator_PickItem::CreatePickItemOperator(bAddToInfiniteBackpack));

		FString SkillName = TEXT("按键:点击, 效果:拾取物品");
		AbilityInfos.Add(USimpleAbilitySkill::CreateSkill(Event, PickConditions, InPickOperators, InOwner, SkillName));
	}
}

void UInteractionAbilityDataAsset::GetDropAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const
{
	if (bCanBePick && !bAddToInfiniteBackpack)
	{
		// 触发类型: 点击, 作用类型: 丢弃
		const UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Click, EInteractionRoleType::Drop);
		const TArray<USimpleAbilityConfigConditionBase*> DropConditions;

		TArray<USimpleAbilityConfigOperatorBase*> DropOperators;
		DropOperators.Add(UInteractionOperator_DropItem::CreateDropItemOperator(DropType));

		FString SkillName = TEXT("按键:点击, 效果:丢弃物品");
		AbilityInfos.Add(USimpleAbilitySkill::CreateSkill(Event, DropConditions, DropOperators, InOwner, SkillName));
	}
}

void UInteractionAbilityDataAsset::GetPutAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const
{
	if (bCanBePick && !bAddToInfiniteBackpack && bCanBePut && PutOperators.Num() > 0)
	{
		// 触发类型: 长按, 作用类型: 放置
		const UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Press, EInteractionRoleType::Put);

		FString SkillName = TEXT("按键:长按, 效果:放置物品");
		AbilityInfos.Add(USimpleAbilitySkill::CreateSkill(Event, PutConditions, PutOperators, InOwner, SkillName));
	}
}

void UInteractionAbilityDataAsset::GetClickAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const
{
	if (bCanBeClick && ClickOperators.Num() > 0)
	{
		for (const EInteractionEffectPlaceType PlaceType : ClickEffectPlaceTypes)
		{
			// 触发类型: 点击, 作用类型: 根据情况选择
			const UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Click, GetRoleTypeByEffectPlaceType(PlaceType));

			FString SkillName = FString::Printf(TEXT("按键:点击, 作用:%s"), *EInteractionRoleTypeToString(PlaceType));
			AbilityInfos.Add(USimpleAbilitySkill::CreateSkill(Event, ClickConditions, ClickOperators, InOwner, SkillName));
		}
	}
}

void UInteractionAbilityDataAsset::GetPressAbilityInfo(AActor* InOwner, TArray<USimpleAbilitySkill*>& AbilityInfos) const
{
	if (bCanBePress && PressOperators.Num() > 0)
	{
		for (const EInteractionEffectPlaceType PlaceType : PressEffectPlaceTypes)
		{
			// 触发类型: 点击, 作用类型: 根据情况选择
			const UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Press, GetRoleTypeByEffectPlaceType(PlaceType));

			FString SkillName = FString::Printf(TEXT("按键:长按, 作用:%s"), *EInteractionRoleTypeToString(PlaceType));
			AbilityInfos.Add(USimpleAbilitySkill::CreateSkill(Event, PressConditions, PressOperators, InOwner, SkillName));
		}
	}
}

EInteractionRoleType UInteractionAbilityDataAsset::GetRoleTypeByEffectPlaceType(const EInteractionEffectPlaceType InEffectPlaceType)
{
	switch (InEffectPlaceType)
	{
	case EInteractionEffectPlaceType::Scene:
		return EInteractionRoleType::Scene;
	case EInteractionEffectPlaceType::Hand:
		return EInteractionRoleType::Hand;
	default:
		ensureAlwaysMsgf(false, TEXT("UInteractionAbilityDataAsset::GetRoleTypeByEffectPlaceType: Invalid EInteractionEffectPlaceType"));
		return EInteractionRoleType::None;
	}
}

FString UInteractionAbilityDataAsset::EInteractionRoleTypeToString(const EInteractionEffectPlaceType InEffectPlaceType)
{
	switch (InEffectPlaceType)
	{
	case EInteractionEffectPlaceType::Scene:
		return TEXT("作用: 场景");
	case EInteractionEffectPlaceType::Hand:
		return TEXT("作用: 手上");
	default:
		ensureAlwaysMsgf(false, TEXT("UInteractionAbilityDataAsset::GetRoleTypeByEffectPlaceType: Invalid EInteractionEffectPlaceType"));
		return TEXT("作用: 无效类型");
	}
}
