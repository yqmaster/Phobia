#include "Component/Interaction/InteractionOperatorBase.h"

void UInteractionOperatorBase::StartDoOperator(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	DoOperatorBegin(OwnerActor, OwnerComponent);
	ReceiveDoOperatorBegin(OwnerActor, OwnerComponent);
}

void UInteractionOperatorBase::EndDoOperator(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	ReceiveDoOperatorEnd(OwnerActor, OwnerComponent);
	DoOperatorEnd(OwnerActor, OwnerComponent);
}

void UInteractionOperatorBase::ReceiveDoOperatorBegin_Implementation(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{

}

void UInteractionOperatorBase::ReceiveDoOperatorEnd_Implementation(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{

}
