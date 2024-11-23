#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

class APCharacterBase;
class UEnhancedInputComponent;

/**
 * 
 */
UCLASS()
class PHOBIA_API APPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	virtual void SetupInputComponent() override;

public:
	UFUNCTION(BlueprintCallable)
	UEnhancedInputComponent* GetEnhancedInputComponent() const;

	UFUNCTION(BlueprintCallable)
	APCharacterBase* GetControlledCharacter() const;
};
