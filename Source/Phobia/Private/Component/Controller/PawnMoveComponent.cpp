#include "Component/Controller/PawnMoveComponent.h"
#include "EnhancedInputComponent.h"
#include "3C/Controller/PPlayerController.h"

UPawnMoveComponent::UPawnMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UPawnMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UPawnMoveComponent::Move);
	}
}


void UPawnMoveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
	{
		// EnhancedInputComponent->BindAction
	}

	Super::EndPlay(EndPlayReason);
}


void UPawnMoveComponent::Move(const FInputActionValue& Value)
{
	if (PlayerController)
	{
		if (APawn* Pawn = PlayerController->K2_GetPawn())
		{
			FVector2D MovementVector = Value.Get<FVector2D>();
			FVector RightVector = Pawn->GetActorRightVector() * MovementVector.X;
			FVector ForwarVector = Pawn->GetActorForwardVector() * MovementVector.Y;
			Pawn->AddMovementInput(RightVector + ForwarVector);
		}
	}
}
