#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "FlashLightComponent.generated.h"

/**
 * @brief 手电组件
 */
UCLASS(Blueprintable, abstract, ClassGroup = (FlashLightComponent))
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
	void UpdateLookAt(float DeltaTime);

	/**
	 * @brief 电量衰减
	 */
	void PowerDecay(float DeltaTime);
	
private:
	// 默认总电量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flash Light", meta = (DisplayName = "电池总电量"), meta = (AllowPrivateAccess = "true"))
	float DefaultFlashLightQuantity;
	// 默认衰减计时
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flash Light", meta = (DisplayName = "延时旋转时间(s)"), meta = (AllowPrivateAccess = "true"))
	float DefaultLatency;

	// 当前电量
	float CurrentQuantity;
	// 初始光源强度
	float InitialIntensity;
	// 光源强度与电池容量比, 用于同步电量与光源强度的衰减量
	float PhotoelectricityRatio;
	// 旋转延时
	float Latency;					
	FRotator TargetRotation;
	FRotator SelfRotation;
};
