#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionPlayerComponent.generated.h"

UCLASS(Blueprintable, abstract, ClassGroup = (Interaction))
class PHOBIA_API UInteractionPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionPlayerComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
