#include "Character/CharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterMovementComponent* ACharacterBase::GetCharacterMovementComponent() const
{
	return GetCharacterMovement<UCharacterMovementComponent>();
}

UCameraComponent* ACharacterBase::GetCameraComponent() const
{
	return GetComponentByClass<UCameraComponent>();
}
