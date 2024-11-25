#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCameraComponent;

UCLASS(Blueprintable, Abstract, Config = Game)
class BASECLASS_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCharacterMovementComponent* GetCharacterMovementComponent() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCameraComponent* GetCameraComponent() const;
};
