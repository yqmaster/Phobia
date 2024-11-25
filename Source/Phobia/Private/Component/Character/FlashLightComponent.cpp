#include "Component/Character/FlashLightComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

UFlashLightComponent::UFlashLightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetVisibility(false);
	CurrentQuantity = DefaultFlashLightQuantity;
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

	if ((bool)CurrentQuantity && GetVisibleFlag())
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
	CurrentQuantity = DefaultFlashLightQuantity;
	SetIntensity(InitialIntensity);
}

void UFlashLightComponent::SetFlashLightParams(float InIntensity, float InInnerConeAngle, float InOuterConeAngle,
                                               float InAttenuationRadius, float InSourceRadius)
{
	PhotoelectricityRatio = InIntensity / DefaultFlashLightQuantity;
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
			Latency = DefaultLatency;
		}

		// 线性插值计算目前阶段的旋转
		float Alpha = Latency / DefaultLatency;
		// bShortestPath必须为true
		FRotator Rotation = UKismetMathLibrary::RLerp(TargetRotation, SelfRotation, Alpha, true);
		SetWorldRotation(Rotation);

		Latency -= DeltaTime;
	}
}

void UFlashLightComponent::PowerDecay(float DeltaTime)
{
	// bVisible控制手电是否耗电
	CurrentQuantity = 0 < CurrentQuantity ? CurrentQuantity - DeltaTime * GetVisibleFlag() : 0;
}
