#include "Character/PCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

APCharacterBase::APCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UCharacterMovementComponent* APCharacterBase::GetCharacterMovementComponent()
{
	return  Cast<UCharacterMovementComponent>(GetMovementComponent());
}

