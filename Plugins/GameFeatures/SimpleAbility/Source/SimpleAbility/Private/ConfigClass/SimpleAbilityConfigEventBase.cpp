#include "ConfigClass/SimpleAbilityConfigEventBase.h"

#include "SimpleAbilitySkill.h"

void USimpleAbilityConfigEventBase::ActiveEvent()
{
	EventActive(GetOwnerActor());
	ReceiveEventActive(GetOwnerActor());
}

void USimpleAbilityConfigEventBase::DeActiveEvent()
{
	ReceiveEventDeActive(GetOwnerActor());
	EventDeActive(GetOwnerActor());
}

void USimpleAbilityConfigEventBase::TriggerEventStart(AActor* InCauser) const
{
	if (!InCauser)
	{
		UE_LOG(SimpleAbility, Error, TEXT("TriggerEventStart Failed, CauserActor is nullptr"));
		return;
	}

	GetOwnerAbilitySkill()->TriggerEventStart(InCauser);
}

void USimpleAbilityConfigEventBase::TriggerEventEnd(AActor* InCauser) const
{
	if (!InCauser)
	{
		UE_LOG(SimpleAbility, Error, TEXT("TriggerEventEnd Failed, CauserActor is nullptr"));
		return;
	}

	GetOwnerAbilitySkill()->TriggerEventEnd(InCauser);
}

FString USimpleAbilityConfigEventBase::GetConfigCategory() const
{
	return TEXT("Event");
}

void USimpleAbilityConfigEventBase::InitConfig(AActor* InOwner, USimpleAbilitySkill* InOwnerSkill)
{
	Super::InitConfig(InOwner, InOwnerSkill);
	InitEvent(InOwner);
	ReceiveInitEvent(InOwner);
}

void USimpleAbilityConfigEventBase::UnInitConfig(AActor* InOwner)
{
	ReceiveUnInitEvent(InOwner);
	UnInitEvent(InOwner);
	Super::UnInitConfig(InOwner);
}
