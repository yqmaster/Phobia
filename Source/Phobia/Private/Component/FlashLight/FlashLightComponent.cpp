// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/FlashLight/FlashLightComponent.h"
#include "Camera/CameraComponent.h"

#define UE_DEFAULT_FLASHLIGHT_QUANTITY 100.f

UFlashLightComponent::UFlashLightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetVisibility(false);
	Quantity = UE_DEFAULT_FLASHLIGHT_QUANTITY;
	// 设定强度单位为流明
	SetIntensityUnits(ELightUnits::Lumens);
}

void UFlashLightComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFlashLightComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateLookAt();
	if ((bool)Quantity && GetVisibleFlag())
	{
		SetIntensity(Intensity - DeltaTime * PhotoelectricityRatio);
	}
}

void UFlashLightComponent::ToggleState()
{
	ToggleVisibility();
}

void UFlashLightComponent::Reset()
{
	Quantity = UE_DEFAULT_FLASHLIGHT_QUANTITY;
	SetIntensity(InitialIntensity);
}

void UFlashLightComponent::SetFlashLightParams(float InIntensity, float InInnerConeAngle, float InOuterConeAngle,
                                               float InAttenuationRadius, float InSourceRadius)
{
	PhotoelectricityRatio = InIntensity / UE_DEFAULT_FLASHLIGHT_QUANTITY;
	InitialIntensity = InIntensity;
	SetIntensity(InIntensity);
	SetInnerConeAngle(InInnerConeAngle);
	SetOuterConeAngle(InOuterConeAngle);
	SetAttenuationRadius(InAttenuationRadius);
	SetSourceRadius(InSourceRadius);
}

void UFlashLightComponent::UpdateLookAt()
{
	if (UCameraComponent* Camera = GetOwner()->GetComponentByClass<UCameraComponent>())
	{
		SetWorldRotation(Camera->GetComponentRotation());
	}
}

void UFlashLightComponent::PowerDecay(float DeltaTime)
{
	Quantity = 0 < Quantity ? Quantity - DeltaTime * GetVisibleFlag() : 0;
}

