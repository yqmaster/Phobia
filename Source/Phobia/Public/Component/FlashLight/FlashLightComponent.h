// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "FlashLightComponent.generated.h"

/**
 * 手电组件
 */
UCLASS()
class PHOBIA_API UFlashLightComponent : public USpotLightComponent
{
	GENERATED_BODY()
public:
	UFlashLightComponent();
private:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/**
	 * @brief 切换手电开关状态
	 */
	UFUNCTION(BlueprintCallable, Category = "Flash Light")
	void ToggleState();

	/**
	 * @brief 重置电量状态
	 */
	UFUNCTION(BlueprintCallable, Category = "Flash Light")
	void Reset();
	
	/**
	 * @brief 设置手电参数
	 * @param InIntensity 光源强度
	 * @param InInnerConeAngle 内圆半径
	 * @param InOuterConeAngle 外圆半径
	 * @param InAttenuationRadius 衰减半径
	 * @param InSourceRadius 源半径
	 */
	UFUNCTION(BlueprintCallable, Category = "Flash Light")
	void SetFlashLightParams(float InIntensity, float InInnerConeAngle, float InOuterConeAngle, float InAttenuationRadius, float InSourceRadius);
protected:
	/**
	 * @brief 更新朝向
	 */
	void UpdateLookAt();

	/**
	 * @brief 电量衰减
	 */
	void PowerDecay(float DeltaTime);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flash Light", meta = (DisplayName = "Quantity"), meta = (AllowPrivateAccess = "true"))
	float Quantity;					// 电量

	float InitialIntensity;			// 初始光源强度
	float PhotoelectricityRatio;	// 光源强度与电池容量比
};
