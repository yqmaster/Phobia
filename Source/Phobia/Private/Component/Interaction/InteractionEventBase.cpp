#include "Component/Interaction/InteractionEventBase.h"

void UInteractionEventBase::EventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	ReceiveEventActive(OwnerActor, OwnerComponent);
}

void UInteractionEventBase::EventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	ReceiveEventDeActive(OwnerActor, OwnerComponent);
}
