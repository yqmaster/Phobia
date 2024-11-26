#include "Component/Interaction/Operators/InteractionOperator_DropItem.h"

#include "Component/Character/Backpack/BackpackComponent.h"

UInteractionOperator_DropItem* UInteractionOperator_DropItem::CreateDropItemOperator(const EDropType InDropType)
{
	UInteractionOperator_DropItem* Operator = NewObject<UInteractionOperator_DropItem>();
	Operator->DropType = InDropType;
	return Operator;
}

void UInteractionOperator_DropItem::DoOperatorBegin(AActor* InOwner, AActor* InCauser)
{
	Super::DoOperatorBegin(InOwner, InCauser);

	if (UBackpackComponent* BackpackComponent = InCauser->FindComponentByClass<UBackpackComponent>())
	{
		BackpackComponent->RemoveCurrentFromBackpack();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s DoOperatorBegin failed, [%s] does not have UBackpackComponent"), *GetConfigInfo(), *InOwner->GetName());
	}
}

void UInteractionOperator_DropItem::DoOperatorEnd(AActor* InOwner, AActor* InCauser)
{
	Super::DoOperatorEnd(InOwner, InCauser);
}
