#include "Component/Backpack/BackPackItemComponent.h"

#include "Camera/CameraComponent.h"
#include "Component/Backpack/BackpackSocketItemComponent.h"
#include "GameFramework/Character.h"

#define UNTOUCHABLE_LOCATION FVector(0.f, 0.f, -10000.f)

void UBackPackItemComponent::BeginPlay()
{
	Super::BeginPlay();

	SetSimulatePhysics(true);
}

void UBackPackItemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SetSimulatePhysics(false);

	Super::EndPlay(EndPlayReason);
}

void UBackPackItemComponent::OnAddToBackpack_Implementation(ACharacter* InTarget, AActor* InItem)
{
	SetSimulatePhysics(false);

	InItem->SetActorLocation(UNTOUCHABLE_LOCATION, false);
	if (const UBackpackSocketItemComponent* SocketComponent = InItem->GetComponentByClass<UBackpackSocketItemComponent>())
	{
		const FTransform& Transform = SocketComponent->GetComponentTransform();
		SetWorldLocation(Transform.GetLocation(), false, nullptr, ETeleportType::TeleportPhysics);
		SetWorldRotation(Transform.GetRotation(), false, nullptr, ETeleportType::TeleportPhysics);
	}
	else
	{
		SetWorldLocation(InTarget->GetActorLocation(), false, nullptr, ETeleportType::TeleportPhysics);
		SetWorldRotation(InTarget->GetActorRotation(), false, nullptr, ETeleportType::TeleportPhysics);
	}
}

void UBackPackItemComponent::OnRemoveFromBackpack_Implementation(ACharacter* InTarget, AActor* InItem)
{
	// 迁移 Actor 的位置和旋转
	FVector Direction;
	FVector Location;
	FRotator Rotation;
	if (const UCameraComponent* CameraComponent = InTarget->FindComponentByClass<UCameraComponent>())
	{
		Direction = CameraComponent->GetForwardVector();
		Location = CameraComponent->GetComponentLocation();
		Rotation = CameraComponent->GetComponentRotation();
	}
	else
	{
		Direction = InTarget->GetActorForwardVector();
		Location = InTarget->GetActorLocation();
		Rotation = InTarget->GetActorRotation();
	}

	InItem->SetActorLocation(Location, false);
	InItem->SetActorRotation(Rotation);

	// 迁移 Component 的位置和旋转
	if (const UBackpackSocketItemComponent* SocketComponent = InItem->GetComponentByClass<UBackpackSocketItemComponent>())
	{
		const FTransform& Transform = SocketComponent->GetComponentTransform();
		SetWorldLocation(Transform.GetLocation(), false, nullptr, ETeleportType::TeleportPhysics);
		SetWorldRotation(Transform.GetRotation(), false, nullptr, ETeleportType::TeleportPhysics);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UBackPackItemComponent::OnRemoveFromBackpack_Implementation: [%s] does not have UBackpackSocketItemComponent"), *InItem->GetName());
		SetWorldLocation(InTarget->GetActorLocation(), false, nullptr, ETeleportType::TeleportPhysics);
		SetWorldRotation(InTarget->GetActorRotation(), false, nullptr, ETeleportType::TeleportPhysics);
	}

	SetSimulatePhysics(true);
	AddForce(Direction * 1000.f * ForceMultiplier, NAME_None, true);
}

void UBackPackItemComponent::OnSetToHand_Implementation(ACharacter* InTarget, AActor* InItem)
{
}

void UBackPackItemComponent::OnUnSetFromHand_Implementation(ACharacter* InTarget, AActor* InItem)
{
}
