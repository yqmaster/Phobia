#include "Component/Interaction/InteractionConditionBase.h"

bool UInteractionConditionBase::CheckCondition(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	return ConditionCheck(OwnerActor, OwnerComponent) & CallConditionCheck(OwnerActor, OwnerComponent);
}

bool UInteractionConditionBase::ConditionCheck(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	return true;
}

bool UInteractionConditionBase::CallConditionCheck_Implementation(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	return true;
}
