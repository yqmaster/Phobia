#include "Component/Interaction/InteractionAbilityDataAsset.h"

#include "Component/Interaction/InteractionAbilityInfo.h"
#include "Component/Interaction/InteractionConditionBase.h"
#include "Component/Interaction/InteractionOperatorBase.h"
#include "Component/Interaction/Events/InteractionEvent_TriggerByInput.h"

TArray<UInteractionAbilityInfo*> UInteractionAbilityDataAsset::GetAllAbilityInfos()
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

void UInteractionAbilityDataAsset::GetPickAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos)
{
	if (bCanBePick)
	{
		// 触发类型: 点击, 作用类型: 拾取
		UInteractionEvent_TriggerByInput* Event = CreateTriggerByInputEvent(EInteractionEventType::Click, EInteractionRoleType::Pick);
		// TODO 这里拾取应该需要额外的条件检查，例如手上是否拿满了
		TArray<TObjectPtr<UInteractionConditionBase>> PickConditions;

		AbilityInfos.Add(CreateAbilityInfo(Event, PickConditions, PickOperators));
	}
}

void UInteractionAbilityDataAsset::GetDropAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos)
{
	if (bCanBePick)
	{
		// 触发类型: 点击, 作用类型: 丢弃
		UInteractionEvent_TriggerByInput* Event = CreateTriggerByInputEvent(EInteractionEventType::Click, EInteractionRoleType::Drop);
		TArray<TObjectPtr<UInteractionConditionBase>> DropConditions;
		// TODO 这里丢弃应该是要根据枚举创建不同的丢弃 Operator
		TArray<TObjectPtr<UInteractionOperatorBase>> DropOperators;

		AbilityInfos.Add(CreateAbilityInfo(Event, DropConditions, DropOperators));
	}
}

void UInteractionAbilityDataAsset::GetPutAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos)
{
	if (bCanBePick && bCanBePut)
	{
		// 触发类型: 长按, 作用类型: 放置
		UInteractionEvent_TriggerByInput* Event = CreateTriggerByInputEvent(EInteractionEventType::Press, EInteractionRoleType::Put);

		AbilityInfos.Add(CreateAbilityInfo(Event, PutConditions, PutOperators));
	}
}

void UInteractionAbilityDataAsset::GetClickAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos)
{
	if (bCanBeClick)
	{
		for (const EInteractionEffectPlaceType PlaceType : ClickEffectPlaceTypes)
		{
			// 触发类型: 点击, 作用类型: 根据情况选择
			UInteractionEvent_TriggerByInput* Event = CreateTriggerByInputEvent(EInteractionEventType::Click, GetRoleTypeByEffectPlaceType(PlaceType));

			AbilityInfos.Add(CreateAbilityInfoWithCopy(Event, ClickConditions, ClickOperators));
		}
	}
}

void UInteractionAbilityDataAsset::GetPressAbilityInfo(TArray<UInteractionAbilityInfo*>& AbilityInfos)
{
	if (bCanBePress)
	{
		for (const EInteractionEffectPlaceType PlaceType : PressEffectPlaceTypes)
		{
			// 触发类型: 点击, 作用类型: 根据情况选择
			UInteractionEvent_TriggerByInput* Event = CreateTriggerByInputEvent(EInteractionEventType::Press, GetRoleTypeByEffectPlaceType(PlaceType));

			AbilityInfos.Add(CreateAbilityInfoWithCopy(Event, PressConditions, PressOperators));
		}
	}
}

UInteractionAbilityInfo* UInteractionAbilityDataAsset::CreateAbilityInfo(UInteractionEventBase* InEvent, const TArray<TObjectPtr<UInteractionConditionBase>>& InConditions, const TArray<TObjectPtr<UInteractionOperatorBase>>& InOperators)
{
	UInteractionAbilityInfo* AbilityInfo = NewObject<UInteractionAbilityInfo>();
	AbilityInfo->Event = InEvent;
	AbilityInfo->Conditions = InConditions;
	AbilityInfo->Operators = InOperators;
	return AbilityInfo;
}

UInteractionAbilityInfo* UInteractionAbilityDataAsset::CreateAbilityInfoWithCopy(const UInteractionEventBase* InEvent, const TArray<TObjectPtr<UInteractionConditionBase>>& InConditions, const TArray<TObjectPtr<UInteractionOperatorBase>>& InOperators)
{
	return CreateAbilityInfo(DuplicateObject(InEvent, this), DuplicateArray<UInteractionConditionBase>(InConditions), DuplicateArray<UInteractionOperatorBase>(InOperators));;
}

UInteractionEvent_TriggerByInput* UInteractionAbilityDataAsset::CreateTriggerByInputEvent(EInteractionEventType InTriggerType, EInteractionRoleType InRoleType)
{
	UInteractionEvent_TriggerByInput* Event = NewObject<UInteractionEvent_TriggerByInput>();
	Event->TriggerType = InTriggerType;
	Event->RoleType = InRoleType;
	return Event;
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
