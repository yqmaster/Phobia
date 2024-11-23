#include "Component/Interaction/InteractionAbilityDataAsset.h"

#include "Component/Interaction/InteractionAbilityInfo.h"
#include "Component/Interaction/InteractionConditionBase.h"
#include "Component/Interaction/InteractionOperatorBase.h"
#include "Component/Interaction/Events/InteractionEvent_TriggerByInput.h"

TArray<UInteractionAbilityInfo*> UInteractionAbilityDataAsset::GetAllAbilityInfos() const
{
	TArray<UInteractionAbilityInfo*> AbilityInfos;

	// 拾取相关
	GetPickAbilityInfo(AbilityInfos);
	// 丢弃相关
	GetDropAbilityInfo(AbilityInfos);
	// 放置相关
	GetPutAbilityInfo(AbilityInfos);
	// 点击相关
	GetClickAbilityInfo(AbilityInfos);
	// 长按相关
	GetPressAbilityInfo(AbilityInfos);

	return AbilityInfos;
}

void UInteractionAbilityDataAsset::GetPickAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos) const
{
	if (bCanBePick && PickOperators.Num() > 0)
	{
		// 触发类型: 点击, 作用类型: 拾取
		UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Click, EInteractionRoleType::Pick);
		// TODO 这里拾取应该需要额外的条件检查，例如手上是否拿满了
		TArray<UInteractionConditionBase*> PickConditions;

		AbilityInfos.Add(UInteractionAbilityInfo::CreateAbilityInfo(Event, PickConditions, PickOperators));
	}
}

void UInteractionAbilityDataAsset::GetDropAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos) const
{
	if (bCanBePick)
	{
		// 触发类型: 点击, 作用类型: 丢弃
		UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Click, EInteractionRoleType::Drop);
		TArray<UInteractionConditionBase*> DropConditions;
		// TODO 这里丢弃应该是要根据枚举创建不同的丢弃 Operator
		TArray<UInteractionOperatorBase*> DropOperators;

		AbilityInfos.Add(UInteractionAbilityInfo::CreateAbilityInfo(Event, DropConditions, DropOperators));
	}
}

void UInteractionAbilityDataAsset::GetPutAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos) const
{
	if (bCanBePick && bCanBePut && PutOperators.Num() > 0)
	{
		// 触发类型: 长按, 作用类型: 放置
		UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Press, EInteractionRoleType::Put);

		AbilityInfos.Add(UInteractionAbilityInfo::CreateAbilityInfo(Event, PutConditions, PutOperators));
	}
}

void UInteractionAbilityDataAsset::GetClickAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos) const
{
	if (bCanBeClick && ClickOperators.Num() > 0)
	{
		for (const EInteractionEffectPlaceType PlaceType : ClickEffectPlaceTypes)
		{
			// 触发类型: 点击, 作用类型: 根据情况选择
			UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Click, GetRoleTypeByEffectPlaceType(PlaceType));

			AbilityInfos.Add(UInteractionAbilityInfo::CreateAbilityInfoWithCopy(Event, ClickConditions, ClickOperators));
		}
	}
}

void UInteractionAbilityDataAsset::GetPressAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos) const
{
	if (bCanBePress && PressOperators.Num() > 0)
	{
		for (const EInteractionEffectPlaceType PlaceType : PressEffectPlaceTypes)
		{
			// 触发类型: 点击, 作用类型: 根据情况选择
			UInteractionEvent_TriggerByInput* Event = UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(EInteractionEventType::Press, GetRoleTypeByEffectPlaceType(PlaceType));

			AbilityInfos.Add(UInteractionAbilityInfo::CreateAbilityInfoWithCopy(Event, PressConditions, PressOperators));
		}
	}
}

EInteractionRoleType UInteractionAbilityDataAsset::GetRoleTypeByEffectPlaceType(EInteractionEffectPlaceType InEffectPlaceType)
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
