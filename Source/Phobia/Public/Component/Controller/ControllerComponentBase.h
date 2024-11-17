#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ControllerComponentBase.generated.h"

class APPlayerController;

UCLASS(BlueprintType, abstract, ClassGroup = (ControllerComponent))
class PHOBIA_API UControllerComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UControllerComponentBase();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UFUNCTION()
	virtual void OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn);

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<APPlayerController> PlayerController = nullptr;
};
