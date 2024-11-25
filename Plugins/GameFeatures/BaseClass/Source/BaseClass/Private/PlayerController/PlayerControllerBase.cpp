#include "PlayerController/PlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "PlayerController/PlayerControllerComponent.h"

TArray<UPlayerControllerComponent*> APlayerControllerBase::GetPlayerControllerComponents() const
{
	TArray<UPlayerControllerComponent*> OutComponents;
	GetComponents<UPlayerControllerComponent>(OutComponents);
	return OutComponents;
}

UEnhancedInputComponent* APlayerControllerBase::GetEnhancedInputComponent() const
{
	return Cast<UEnhancedInputComponent>(InputComponent);
}

ACharacter* APlayerControllerBase::GetControlledCharacter() const
{
	return Cast<ACharacter>(GetPawn());
}

void APlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ACharacter* CharacterBase = Cast<ACharacter>(InPawn))
	{
		for (UPlayerControllerComponent* Component : GetPlayerControllerComponents())
		{
			Component->PossessCharacter(this, CharacterBase);
		}
	}
}

void APlayerControllerBase::OnUnPossess()
{
	if (GetControlledCharacter())
	{
		for (UPlayerControllerComponent* Component : GetPlayerControllerComponents())
		{
			Component->UnPossessCharacter();
		}
	}

	Super::OnUnPossess();
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* InInputComponent = GetEnhancedInputComponent())
	{
		for (UPlayerControllerComponent* Component : GetPlayerControllerComponents())
		{
			Component->SetupInputComponent(InInputComponent);
		}
	}
}
