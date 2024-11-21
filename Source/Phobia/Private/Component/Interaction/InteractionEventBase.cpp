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

void UInteractionEventBase::TriggerEventStart()
{
	if (AbilityInfo)
	{
		AbilityInfo->TriggerAbilityInfoEventStart();
	}
}

void UInteractionEventBase::TriggerEventEnd()
{
	if (AbilityInfo)
	{
		AbilityInfo->TriggerAbilityInfoEventEnd();
	}
}

void UInteractionEventBase::CallTriggerEventStart()
{
	TriggerEventStart();
}


void UInteractionEventBase::CallTriggerEventEnd()
{
	TriggerEventEnd();
}
