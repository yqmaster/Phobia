#include "Component/Interaction/InteractionItemComponent.h"

#include "Component/Interaction/InteractionAbilityDataAsset.h"
#include "Component/Interaction/InteractionAbilityInfo.h"

UInteractionItemComponent::UInteractionItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionItemComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwnerActor = GetOwner();

	ensureAlwaysMsgf(AbilityInfos.IsEmpty(), TEXT("[%s] in [%s] AbilityInfos is not empty when BeginPlay"), *GetName(), *OwnerActor->GetName());
	AbilityInfos.Empty();
	if (InteractionAbilityAsset)
	{
		for (UInteractionAbilityInfo* AbilityInfo : InteractionAbilityAsset->GetAllAbilityInfos(OwnerActor))
		{
			ensureAlwaysMsgf(AbilityInfo, TEXT("[%s] passing a nullptr AbilityInfo from GetAllAbilityInfos in [%s]"), *InteractionAbilityAsset->GetName(), *OwnerActor->GetName());
			if (AbilityInfo)
			{
				AbilityInfo->InitAbilityInfo(OwnerActor, this);
				AbilityInfos.Add(AbilityInfo);
			}
		}
	}

	for (const UInteractionAbilityInfo* AbilityInfo : AbilityInfos)
	{
		AbilityInfo->ActiveAbilityInfo();
	}
}

void UInteractionItemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AActor* OwnerActor = GetOwner();

	for (UInteractionAbilityInfo* AbilityInfo : AbilityInfos)
	{
		ensureAlwaysMsgf(AbilityInfo, TEXT("[%s] has invalid AbilityInfo when EndPlay in [%s]"), *GetName(), *OwnerActor->GetName());
		AbilityInfo->DeActiveAbilityInfo();
		AbilityInfo->UnInitAbilityInfo(OwnerActor, this);
	}

	Super::EndPlay(EndPlayReason);
}

void UInteractionItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionItemComponent::TakeInteractionByClick(AActor* Taker, const EInteractionRoleType RoleType) const
{
	OnInteractByClick.Broadcast(Taker, RoleType);
}

void UInteractionItemComponent::TakeInteractionByPress(AActor* Taker, const EInteractionRoleType RoleType, const bool IsStart) const
{
	OnInteractByPress.Broadcast(Taker, RoleType, IsStart);
}
