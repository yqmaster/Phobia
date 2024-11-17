#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/PCharacterBase.h"
#include "PPlayerController.generated.h"

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

public:
	UFUNCTION(BlueprintCallable)
	UEnhancedInputComponent* GetEnhancedInputComponent() const;

	UFUNCTION(BlueprintCallable)
	APCharacterBase* GetControlledCharacter() const;
};
