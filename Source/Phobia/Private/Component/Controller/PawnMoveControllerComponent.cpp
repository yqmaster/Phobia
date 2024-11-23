#include "Component/Controller/PawnMoveControllerComponent.h"

#include "EnhancedInputComponent.h"
#include "3C/Controller/PPlayerController.h"
#include "Character/PCharacterBase.h"
#include "Component/Character/PawnMoveComponent.h"

void UPawnMoveControllerComponent::OnSetupInputComponent(UEnhancedInputComponent* InInputComponent)
{
	Super::OnSetupInputComponent(InInputComponent);

	if (InInputComponent)
	{
		// 移动
		InInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UPawnMoveControllerComponent::Move);
		// 冲刺
		InInputComponent->BindAction(RushAction, ETriggerEvent::Started, this, &UPawnMoveControllerComponent::StartRush);
		InInputComponent->BindAction(RushAction, ETriggerEvent::Completed, this, &UPawnMoveControllerComponent::EndRush);
	}
}

void UPawnMoveControllerComponent::OnPossessed(APCharacterBase* InCharacter)
{
	Super::OnPossessed(InCharacter);

	CachePawnMoveComponent();
}

void UPawnMoveControllerComponent::OnUnPossessed()
{
	UnCachePawnMoveComponent();

	Super::OnUnPossessed();
}

void UPawnMoveControllerComponent::Move(const FInputActionValue& InValue)
{
	if (PawnMoveComponent)
	{
		PawnMoveComponent->Move(InValue.Get<FVector2D>());
	}
}

void UPawnMoveControllerComponent::StartRush(const FInputActionValue& InValue)
{
	if (PawnMoveComponent)
	{
		PawnMoveComponent->StartRush();
	}
}

void UPawnMoveControllerComponent::EndRush(const FInputActionValue& InValue)
{
	if (PawnMoveComponent)
	{
		PawnMoveComponent->EndRush();
	}
}

void UPawnMoveControllerComponent::CachePawnMoveComponent()
{
	if (const APPlayerController* PC = GetPlayerController())
	{
		if (const APCharacterBase* Character = PC->GetControlledCharacter())
		{
			UPawnMoveComponent* Component = Character->GetComponentByClass<UPawnMoveComponent>();
			if (!Component)
			{
				UE_LOG(LogTemp, Error, TEXT("[%s] init failed, [%s] does not have UPawnMoveComponent"), *GetName(), *Character->GetName());
				return;
			}

			PawnMoveComponent = Component;
		}
	}
}

void UPawnMoveControllerComponent::UnCachePawnMoveComponent()
{
	PawnMoveComponent = nullptr;
}
