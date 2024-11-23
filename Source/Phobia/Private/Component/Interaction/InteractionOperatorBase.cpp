#include "Component/Interaction/InteractionOperatorBase.h"

void UInteractionOperatorBase::StartDoOperator(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	DoOperatorBegin(TakerActor, OwnerActor, OwnerComponent);
	ReceiveDoOperatorBegin(TakerActor, OwnerActor, OwnerComponent);
}

void UInteractionOperatorBase::EndDoOperator(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	ReceiveDoOperatorEnd(TakerActor, OwnerActor, OwnerComponent);
	DoOperatorEnd(TakerActor, OwnerActor, OwnerComponent);
}
