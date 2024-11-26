#include "Component/Interaction/Operators/InteractionOperator_PickItem.h"

#include "Component/Character/Backpack/BackpackComponent.h"

UInteractionOperator_PickItem* UInteractionOperator_PickItem::CreatePickItemOperator(const bool bAddInfiniteBackpack)
{
	UInteractionOperator_PickItem* Operator = NewObject<UInteractionOperator_PickItem>();
	Operator->bAddInfiniteBackpack = bAddInfiniteBackpack;
	return Operator;
}

void UInteractionOperator_PickItem::DoOperatorBegin(AActor* InOwner, AActor* InCauser)
{
	Super::DoOperatorBegin(InOwner, InCauser);

	if (UBackpackComponent* BackpackComponent = InCauser->FindComponentByClass<UBackpackComponent>())
	{
		if (bAddInfiniteBackpack)
		{
			BackpackComponent->AddToInfiniteBackpack(InOwner);
		}
		else
		{
			BackpackComponent->AddToBackpack(InOwner);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s DoOperatorBegin failed, [%s] does not have UBackpackComponent"), *GetConfigInfo(), *InCauser->GetName());
	}
}

void UInteractionOperator_PickItem::DoOperatorEnd(AActor* InOwner, AActor* InCauser)
{
	Super::DoOperatorEnd(InOwner, InCauser);
}
