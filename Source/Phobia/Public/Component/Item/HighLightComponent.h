#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/DetectedItemInterface.h"
#include "HighLightComponent.generated.h"

UCLASS(Blueprintable, abstract, ClassGroup =(Item))
class PHOBIA_API UHighLightComponent : public UActorComponent, public IDetectedItemInterface
{
	GENERATED_BODY()

public:
	UHighLightComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnDetected_Implementation(AActor* InOwner, bool bHighLight) override;
};
