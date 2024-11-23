#include "Component/Controller/ControllerComponentBase.h"
#include "3C/Controller/PPlayerController.h"

void UControllerComponentBase::SetupInputComponent(UEnhancedInputComponent* InInputComponent)
{
	CachedInputComponent = InInputComponent;
	ensureAlwaysMsgf(CachedInputComponent, TEXT("SetupInputComponent for [%s] at [%s] failed, InputComponent is nullptr"), *GetName(), *GetOwner()->GetName());
	if (CachedInputComponent)
	{
		OnSetupInputComponent(CachedInputComponent);
		ReceiveOnSetupInputComponent(CachedInputComponent);
	}
}

void UControllerComponentBase::PossessCharacter(APlayerController* InPlayerController, APCharacterBase* InCharacter)
{
	CachedPlayerCharacter = InCharacter;
	CachedPlayerController = Cast<APPlayerController>(InPlayerController);

	OnPossessed(InCharacter);
	ReceiveOnPossessed(InCharacter);
}

void UControllerComponentBase::UnPossessCharacter()
{
	ReceiveOnUnPossessed();
	OnUnPossessed();

	CachedPlayerController = nullptr;
	CachedPlayerCharacter = nullptr;
	CachedInputComponent = nullptr;
}

UEnhancedInputComponent* UControllerComponentBase::GetInputComponent() const
{
	if (CachedInputComponent)
	{
		return CachedInputComponent;
	}

	ensureAlwaysMsgf(false, TEXT("GetInputComponent for [%s] at [%s] failed, InputComponent is nullptr"), *GetName(), *GetOwner()->GetName());
	const APPlayerController* Controller = GetPlayerController();
	return Controller ? Controller->GetEnhancedInputComponent() : nullptr;
}

APPlayerController* UControllerComponentBase::GetPlayerController() const
{
	if (CachedPlayerController)
	{
		return CachedPlayerController;
	}

	ensureAlwaysMsgf(false, TEXT("GetPlayerController for [%s] at [%s] failed, PlayerController is nullptr"), *GetName(), *GetOwner()->GetName());
	return Cast<APPlayerController>(GetOwner());
}

APCharacterBase* UControllerComponentBase::GetControlledCharacter() const
{
	if (const APPlayerController* PC = GetPlayerController())
	{
		return PC->GetControlledCharacter();
	}

	ensureAlwaysMsgf(false, TEXT("GetControlledCharacter for [%s] at [%s] failed, PlayerController is nullptr"), *GetName(), *GetOwner()->GetName());
	return nullptr;
}
