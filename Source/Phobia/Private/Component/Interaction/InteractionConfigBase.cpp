#include "Component/Interaction/InteractionConfigBase.h"

void UInteractionConfigBase::Init(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent, UInteractionAbilityInfo* OwnerAbilityInfo)
{
	AbilityInfo = OwnerAbilityInfo;
	OnInit(OwnerActor, OwnerComponent);
	ReceiveOnInit(OwnerActor, OwnerComponent);
}

void UInteractionConfigBase::UnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent, UInteractionAbilityInfo* OwnerAbilityInfo)
{
	ReceiveOnUnInit(OwnerActor, OwnerComponent);
	OnUnInit(OwnerActor, OwnerComponent);
	AbilityInfo = nullptr;
}

void UInteractionConfigBase::OnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
}

void UInteractionConfigBase::OnUnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
}
