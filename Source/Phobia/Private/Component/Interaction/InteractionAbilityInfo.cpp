#include "Component/Interaction/InteractionAbilityInfo.h"

#include "Component/Interaction/InteractionConditionBase.h"
#include "Component/Interaction/InteractionEventBase.h"
#include "Component/Interaction/InteractionOperatorBase.h"

UInteractionAbilityInfo* UInteractionAbilityInfo::CreateAbilityInfo(const FString& InAbilityInfoName, const UInteractionEventBase* InEvent, const TArray<UInteractionConditionBase*>& InConditions, const TArray<UInteractionOperatorBase*>& InOperators)
{
	UE_LOG(LogTemp, Log, TEXT("CreateAbilityInfo for %s"), *InAbilityInfoName);
	UInteractionAbilityInfo* AbilityInfo = NewObject<UInteractionAbilityInfo>();
	AbilityInfo->AbilityInfoName = InAbilityInfoName;
	AbilityInfo->Event = DuplicateObject<UInteractionEventBase>(InEvent, nullptr);
	AbilityInfo->Conditions = DuplicateTObjectArray(InConditions);
	AbilityInfo->Operators = DuplicateTObjectArray(InOperators);
	return AbilityInfo;
}

void UInteractionAbilityInfo::InitAbilityInfo(AActor* InOwnerActor, UInteractionItemComponent* InOwnerComponent)
{
	UE_LOG(LogTemp, Log, TEXT("InitAbilityInfo for %s"), *AbilityInfoName);
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
	UE_LOG(LogTemp, Log, TEXT("UnInitAbilityInfo for %s"), *AbilityInfoName);
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

void UInteractionAbilityInfo::ActiveAbilityInfo() const
{
	UE_LOG(LogTemp, Log, TEXT("ActiveAbilityInfo for %s"), *AbilityInfoName);
	if (Event)
	{
		Event->ActiveEvent(OwnerActor, OwnerComponent);
	}
}

void UInteractionAbilityInfo::DeActiveAbilityInfo() const
{
	UE_LOG(LogTemp, Log, TEXT("DeActiveAbilityInfo for %s"), *AbilityInfoName);
	if (Event)
	{
		Event->DeActiveEvent(OwnerActor, OwnerComponent);
	}
}

void UInteractionAbilityInfo::TriggerAbilityInfoEventStart(AActor* TakerActor)
{
	UE_LOG(LogTemp, Log, TEXT("TriggerAbilityInfoEventStart for %s"), *AbilityInfoName);
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
	UE_LOG(LogTemp, Log, TEXT("TriggerAbilityInfoEventEnd for %s"), *AbilityInfoName);
	StartingOperators.RemoveAllSwap([this, TakerActor](UInteractionOperatorBase* Operator)
	{
		Operator->EndDoOperator(TakerActor, OwnerActor, OwnerComponent);
		return true;
	});
}
