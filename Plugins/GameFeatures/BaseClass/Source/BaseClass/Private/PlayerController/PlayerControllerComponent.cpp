#include "PlayerController/PlayerControllerComponent.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

void UPlayerControllerComponent::SetupInputComponent(UEnhancedInputComponent* InInputComponent)
{
	CachedInputComponent = InInputComponent;
	ensureAlwaysMsgf(CachedInputComponent, TEXT("SetupInputComponent for [%s] in [%s] failed, InputComponent is nullptr"), *GetName(), *GetOwner()->GetName());
	if (CachedInputComponent)
	{
		OnSetupInputComponent(CachedInputComponent);
		ReceiveOnSetupInputComponent(CachedInputComponent);
	}
}

void UPlayerControllerComponent::PossessCharacter(APlayerController* InPlayerController, ACharacter* InCharacter)
{
	CachedPlayerCharacter = InCharacter;
	CachedPlayerController = InPlayerController;

	OnPossessed(InCharacter);
	ReceiveOnPossessed(InCharacter);
}

void UPlayerControllerComponent::UnPossessCharacter()
{
	ReceiveOnUnPossessed();
	OnUnPossessed();

	CachedPlayerController = nullptr;
	CachedPlayerCharacter = nullptr;
	CachedInputComponent = nullptr;
}

UEnhancedInputComponent* UPlayerControllerComponent::GetInputComponent() const
{
	if (CachedInputComponent)
	{
		return CachedInputComponent;
	}

	ensureAlwaysMsgf(false, TEXT("GetInputComponent for [%s] in [%s] failed, CachedInputComponent is nullptr"), *GetName(), *GetOwner()->GetName());
	const APlayerController* PC = GetPlayerController();
	return PC ? Cast<UEnhancedInputComponent>(PC->InputComponent) : nullptr;
}

APlayerController* UPlayerControllerComponent::GetPlayerController() const
{
	if (CachedPlayerController)
	{
		return CachedPlayerController;
	}

	ensureAlwaysMsgf(false, TEXT("GetPlayerController for [%s] in [%s] failed, CachedPlayerController is nullptr"), *GetName(), *GetOwner()->GetName());
	return Cast<APlayerController>(GetOwner());
}

ACharacter* UPlayerControllerComponent::GetControlledCharacter() const
{
	if (CachedPlayerCharacter)
	{
		return CachedPlayerCharacter;
	}

	ensureAlwaysMsgf(false, TEXT("GetControlledCharacter for [%s] in [%s] failed, CachedPlayerCharacter is nullptr"), *GetName(), *GetOwner()->GetName());
	const APlayerController* PC = GetPlayerController();
	return PC ? Cast<ACharacter>(PC->GetPawn()) : nullptr;
}
