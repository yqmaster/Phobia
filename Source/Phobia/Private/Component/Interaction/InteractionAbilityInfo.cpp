#include "Component/Interaction/InteractionAbilityInfo.h"

#include "Component/Interaction/InteractionEventBase.h"

void UInteractionAbilityInfo::InitAbilityInfo(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	if (Event)
	{
		Event->EventActive(OwnerActor, OwnerComponent);
	}
}

void UInteractionAbilityInfo::UnInitAbilityInfo(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	if (Event)
	{
		Event->EventDeActive(OwnerActor, OwnerComponent);
	}
}
