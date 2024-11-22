#include "Component/Interaction/InteractionAbilityInfo.h"

#include "Component/Interaction/InteractionConditionBase.h"
#include "Component/Interaction/InteractionEventBase.h"
#include "Component/Interaction/InteractionOperatorBase.h"

void UInteractionAbilityInfo::InitAbilityInfo(AActor* InOwnerActor, UInteractionItemComponent* InOwnerComponent)
{
	OwnerActor = InOwnerActor;
	OwnerComponent = InOwnerComponent;

	if (Event)
	{
		Event->Init(OwnerActor, OwnerComponent, this);
	}

	for (UInteractionConditionBase* Condition : Conditions)
	{
		Condition->Init(OwnerActor, OwnerComponent, this);
	}

	for (UInteractionOperatorBase* Operator : Operators)
	{
		Operator->Init(OwnerActor, OwnerComponent, this);
	}
}

void UInteractionAbilityInfo::UnInitAbilityInfo(AActor* InOwnerActor, UInteractionItemComponent* InOwnerComponent)
{
	if (Event)
	{
		Event->UnInit(OwnerActor, OwnerComponent, this);
	}

	for (UInteractionConditionBase* Condition : Conditions)
	{
		Condition->UnInit(OwnerActor, OwnerComponent, this);
	}

	for (UInteractionOperatorBase* Operator : Operators)
	{
		Operator->UnInit(OwnerActor, OwnerComponent, this);
	}

	OwnerActor = nullptr;
	OwnerComponent = nullptr;
}

void UInteractionAbilityInfo::ActiveAbilityInfo()
{
	if (Event)
	{
		Event->ActiveEvent(OwnerActor, OwnerComponent);
	}
}

void UInteractionAbilityInfo::DeActiveAbilityInfo()
{
	if (Event)
	{
		Event->DeActiveEvent(OwnerActor, OwnerComponent);
	}
}

void UInteractionAbilityInfo::TriggerAbilityInfoEventStart(AActor* TakerActor)
{
	// 条件检查
	bool CheckCondition = true;
	for (UInteractionConditionBase* Condition : Conditions)
	{
		CheckCondition &= Condition->CheckCondition(OwnerActor, OwnerComponent);
	}

	// 有一个条件不满足就取消
	if (!CheckCondition)
	{
		return;
	}

	for (UInteractionOperatorBase* Operator : Operators)
	{
		Operator->StartDoOperator(TakerActor, OwnerActor, OwnerComponent);
		StartingOperators.Add(Operator);
	}
}

void UInteractionAbilityInfo::TriggerAbilityInfoEventEnd(AActor* TakerActor)
{
	StartingOperators.RemoveAllSwap([this, TakerActor](UInteractionOperatorBase* Operator)
	{
		Operator->EndDoOperator(TakerActor, OwnerActor, OwnerComponent);
		return true;
	});
}
