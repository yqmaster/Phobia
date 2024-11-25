#include "Character/CharacterComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

void UCharacterComponent::BeginPlay()
{
	CachedCharacter = Cast<ACharacter>(GetOwner());
	CachedMovementComponent = GetOwner()->GetComponentByClass<UCharacterMovementComponent>();
	CachedCameraComponent = GetOwner()->GetComponentByClass<UCameraComponent>();

	Super::BeginPlay();
}

void UCharacterComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	CachedCameraComponent = nullptr;
	CachedMovementComponent = nullptr;
	CachedCharacter = nullptr;
}

ACharacter* UCharacterComponent::GetOwnerCharacter() const
{
	if (CachedCharacter)
	{
		return CachedCharacter;
	}

	ensureAlwaysMsgf(false, TEXT("GetCharacter for [%s] in [%s] failed, CachedCharacter is nullptr"), *GetName(), *GetOwner()->GetName());
	return Cast<ACharacter>(GetOwner());
}

UCharacterMovementComponent* UCharacterComponent::GetCharacterMovementComponent() const
{
	if (CachedMovementComponent)
	{
		return CachedMovementComponent;
	}

	ensureAlwaysMsgf(false, TEXT("GetCharacterMovementComponent for [%s] in [%s] failed, CachedMovementComponent is nullptr"), *GetName(), *GetOwner()->GetName());
	return GetOwner()->GetComponentByClass<UCharacterMovementComponent>();
}

UCameraComponent* UCharacterComponent::GetCameraComponent() const
{
	if (CachedCameraComponent)
	{
		return CachedCameraComponent;
	}

	ensureAlwaysMsgf(false, TEXT("GetCameraComponent for [%s] in [%s] failed, CachedCameraComponent is nullptr"), *GetName(), *GetOwner()->GetName());
	return GetOwner()->GetComponentByClass<UCameraComponent>();
}
