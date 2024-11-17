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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable)
	UCharacterMovementComponent* GetCharacterMovementComponent();
};
