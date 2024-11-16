#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCharacterBase.generated.h"

UCLASS()
class PHOBIA_API APCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
