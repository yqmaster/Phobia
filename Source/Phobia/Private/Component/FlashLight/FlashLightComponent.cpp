// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/FlashLight/FlashLightComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

#define UE_DEFAULT_FLASH_LIGHT_QUANTITY 100.f	// 电池电量
#define UE_DEFAULT_FLASH_LIGHT_LATENCY 0.15f	// 计时器持续时间
UFlashLightComponent::UFlashLightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetVisibility(false);
	Quantity = UE_DEFAULT_FLASH_LIGHT_QUANTITY;
	Latency = -1.f;
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
	
	UpdateLookAt(DeltaTime);
	
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
	Quantity = UE_DEFAULT_FLASH_LIGHT_QUANTITY;
	SetIntensity(InitialIntensity);
}

void UFlashLightComponent::SetFlashLightParams(float InIntensity, float InInnerConeAngle, float InOuterConeAngle,
                                               float InAttenuationRadius, float InSourceRadius)
{
	PhotoelectricityRatio = InIntensity / UE_DEFAULT_FLASH_LIGHT_QUANTITY;
	InitialIntensity = InIntensity;
	SetIntensity(InIntensity);
	SetInnerConeAngle(InInnerConeAngle);
	SetOuterConeAngle(InOuterConeAngle);
	SetAttenuationRadius(InAttenuationRadius);
	SetSourceRadius(InSourceRadius);
}

void UFlashLightComponent::UpdateLookAt(float DeltaTime)
{
	if (UCameraComponent* Camera = GetOwner()->GetComponentByClass<UCameraComponent>())
	{
		// 计时结束进入更新初始值和目标值并重新计时
		if (0.f > Latency)
		{
			TargetRotation = Camera->GetComponentRotation();
			SelfRotation = GetComponentRotation();
			Latency = UE_DEFAULT_FLASH_LIGHT_LATENCY;
		}

		// 线性插值计算目前阶段的旋转
		float Alpha = Latency / UE_DEFAULT_FLASH_LIGHT_LATENCY;
		// bShortestPath必须为true
		FRotator Rotation = UKismetMathLibrary::RLerp(TargetRotation, SelfRotation, Alpha, true);
		SetWorldRotation(Rotation);
		
		Latency -= DeltaTime;
	}
}

void UFlashLightComponent::PowerDecay(float DeltaTime)
{
	// bVisible控制手电是否耗电
	Quantity = 0 < Quantity ? Quantity - DeltaTime * GetVisibleFlag() : 0;
}

