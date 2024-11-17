#include "3C/Controller/PPlayerController.h"
#include "EnhancedInputComponent.h"

void APPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

}

void APPlayerController::OnUnPossess()
{
    Super::OnUnPossess();

}

UEnhancedInputComponent* APPlayerController::GetEnhancedInputComponent() const
{
    return Cast<UEnhancedInputComponent>(InputComponent);
}

APCharacterBase* APPlayerController::GetControlledCharacter() const
{
    return Cast<APCharacterBase>(K2_GetPawn());
}
