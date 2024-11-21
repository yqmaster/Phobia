#include "Component/Interaction/Events/InteractionEvent_TriggerInScene.h"
#include "Component/Interaction/InteractionItemComponent.h"

void UInteractionEvent_TriggerInScene::EventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	Super::EventActive(OwnerActor, OwnerComponent);

	if (OwnerComponent)
	{
		OwnerComponent->OnInteractOnScene.AddDynamic(this, &UInteractionEvent_TriggerInScene::OnInteractionInScene);
	}
}

void UInteractionEvent_TriggerInScene::EventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	if (OwnerComponent)
	{
		OwnerComponent->OnInteractOnScene.RemoveDynamic(this, &UInteractionEvent_TriggerInScene::OnInteractionInScene);
	}

	Super::EventDeActive(OwnerActor, OwnerComponent);
}

void UInteractionEvent_TriggerInScene::OnInteractionInScene(ETriggerEvent InTriggerEvent)
{
	TriggerEventStart();
	TriggerEventEnd();
}
