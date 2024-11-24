#include "Component/Interaction/Operators/InteractionOperator_DropItem.h"

#include "Component/Backpack/BackpackComponent.h"

UInteractionOperator_DropItem* UInteractionOperator_DropItem::CreateDropItemOperator(const EDropType InDropType)
{
	UInteractionOperator_DropItem* Operator = NewObject<UInteractionOperator_DropItem>();
	Operator->DropType = InDropType;
	return Operator;
}

void UInteractionOperator_DropItem::DoOperatorBegin(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	Super::DoOperatorBegin(TakerActor, OwnerActor, OwnerComponent);

	if (UBackpackComponent* BackpackComponent = TakerActor->FindComponentByClass<UBackpackComponent>())
	{
		BackpackComponent->RemoveCurrentFromBackpack();
	}
}

void UInteractionOperator_DropItem::DoOperatorEnd(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	Super::DoOperatorEnd(TakerActor, OwnerActor, OwnerComponent);
}
