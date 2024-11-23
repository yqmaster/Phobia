#include "3C/Controller/PPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Character/PCharacterBase.h"
#include "Component/Controller/ControllerComponentBase.h"

void APPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (APCharacterBase* CharacterBase = Cast<APCharacterBase>(InPawn))
	{
		TArray<UControllerComponentBase*> Components;
		GetComponents(UControllerComponentBase::StaticClass(), Components);
		for (UControllerComponentBase* Component : Components)
		{
			Component->PossessCharacter(this, CharacterBase);
		}
	}
}

void APPlayerController::OnUnPossess()
{
	if (APCharacterBase* CharacterBase = GetControlledCharacter())
	{
		TArray<UControllerComponentBase*> Components;
		GetComponents(UControllerComponentBase::StaticClass(), Components);
		for (UControllerComponentBase* Component : Components)
		{
			Component->UnPossessCharacter();
		}
	}

	Super::OnUnPossess();
}

void APPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* InInputComponent = GetEnhancedInputComponent())
	{
		TArray<UControllerComponentBase*> Components;
		GetComponents(UControllerComponentBase::StaticClass(), Components);
		for (UControllerComponentBase* Component : Components)
		{
			Component->SetupInputComponent(InInputComponent);
		}
	}
}

UEnhancedInputComponent* APPlayerController::GetEnhancedInputComponent() const
{
	return Cast<UEnhancedInputComponent>(InputComponent);
}

APCharacterBase* APPlayerController::GetControlledCharacter() const
{
	return Cast<APCharacterBase>(K2_GetPawn());
}
