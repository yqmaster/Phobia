#include "Component/Controller/PawnMoveControllerComponent.h"

#include "EnhancedInputComponent.h"
#include "3C/Controller/PPlayerController.h"
#include "Component/Character/PawnMoveComponent.h"

UPawnMoveControllerComponent::UPawnMoveControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPawnMoveControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
	{
		// 移动
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UPawnMoveControllerComponent::Move);
		// 冲刺
		EnhancedInputComponent->BindAction(RushAction, ETriggerEvent::Started, this, &UPawnMoveControllerComponent::StartRush);
		EnhancedInputComponent->BindAction(RushAction, ETriggerEvent::Completed, this, &UPawnMoveControllerComponent::EndRush);
	}

	CachePawnMoveComponent(PlayerController->GetControlledCharacter());
}

void UPawnMoveControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// TODO UnbindAction

	Super::EndPlay(EndPlayReason);
}

void UPawnMoveControllerComponent::OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn)
{
	Super::OnPossessedPawnChange(OldPawn, NewPawn);

	CachePawnMoveComponent(NewPawn);
}

void UPawnMoveControllerComponent::Move(const FInputActionValue& Value)
{
	if (PawnMoveComponent)
	{
		PawnMoveComponent->Move(Value.Get<FVector2D>());
	}
}

void UPawnMoveControllerComponent::StartRush(const FInputActionValue& Value)
{
	if (PawnMoveComponent)
	{
		PawnMoveComponent->StartRush();
	}
}

void UPawnMoveControllerComponent::EndRush(const FInputActionValue& Value)
{
	if (PawnMoveComponent)
	{
		PawnMoveComponent->EndRush();
	}
}

void UPawnMoveControllerComponent::CachePawnMoveComponent(const AActor* InActor)
{
	if (InActor)
	{
		UPawnMoveComponent* Component = InActor->GetComponentByClass<UPawnMoveComponent>();
		if (!Component)
		{
			UE_LOG(LogTemp, Error, TEXT("[%s] init failed, [%s] does not have UPawnMoveComponent"), *GetName(), *InActor->GetName());
			return;
		}

		PawnMoveComponent = Component;
	}
}
