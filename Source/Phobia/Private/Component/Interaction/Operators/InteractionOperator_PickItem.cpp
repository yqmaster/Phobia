#include "Component/Interaction/Operators/InteractionOperator_PickItem.h"

#include "Component/Character/Backpack/BackpackComponent.h"

UInteractionOperator_PickItem* UInteractionOperator_PickItem::CreatePickItemOperator(const bool bAddInfiniteBackpack)
{
	UInteractionOperator_PickItem* Operator = NewObject<UInteractionOperator_PickItem>();
	Operator->bAddInfiniteBackpack = bAddInfiniteBackpack;
	return Operator;
}

void UInteractionOperator_PickItem::DoOperatorBegin(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	Super::DoOperatorBegin(TakerActor, OwnerActor, OwnerComponent);

	if (UBackpackComponent* BackpackComponent = TakerActor->FindComponentByClass<UBackpackComponent>())
	{
		if (bAddInfiniteBackpack)
		{
			BackpackComponent->AddToInfiniteBackpack(OwnerActor);
		}
		else
		{
			BackpackComponent->AddToBackpack(OwnerActor);
		}
	}
}

void UInteractionOperator_PickItem::DoOperatorEnd(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	Super::DoOperatorEnd(TakerActor, OwnerActor, OwnerComponent);
}
