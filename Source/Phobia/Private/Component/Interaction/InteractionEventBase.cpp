#include "Component/Interaction/InteractionEventBase.h"

#include "Component/Interaction/InteractionAbilityInfo.h"

void UInteractionEventBase::ActiveEvent(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	EventActive(OwnerActor, OwnerComponent);
	ReceiveEventActive(OwnerActor, OwnerComponent);
}

void UInteractionEventBase::DeActiveEvent(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	ReceiveEventDeActive(OwnerActor, OwnerComponent);
	EventDeActive(OwnerActor, OwnerComponent);
}

void UInteractionEventBase::TriggerEventStart(AActor* TakerActor) const
{
	if (AbilityInfo)
	{
		AbilityInfo->TriggerAbilityInfoEventStart(TakerActor);
	}
}

void UInteractionEventBase::TriggerEventEnd(AActor* TakerActor) const
{
	if (AbilityInfo)
	{
		AbilityInfo->TriggerAbilityInfoEventEnd(TakerActor);
	}
}

void UInteractionEventBase::CallTriggerEventStart(AActor* TakerActor)
{
	TriggerEventStart(TakerActor);
}

void UInteractionEventBase::CallTriggerEventEnd(AActor* TakerActor)
{
	TriggerEventEnd(TakerActor);
}
