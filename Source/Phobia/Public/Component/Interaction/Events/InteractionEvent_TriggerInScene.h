#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionEventBase.h"
#include "InteractionEvent_TriggerInScene.generated.h"

enum class ETriggerEvent : uint8;

/**
 *
 */
UCLASS(Blueprintable, EditInlineNew, meta = (DisplayName = "场景中交互"))
class PHOBIA_API UInteractionEvent_TriggerInScene : public UInteractionEventBase
{
	GENERATED_BODY()

public:
	virtual void EventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) override;

	virtual void EventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) override;

private:
	UFUNCTION()
	void OnInteractionInScene(ETriggerEvent TriggerType);
};
