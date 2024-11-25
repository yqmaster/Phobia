#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterComponent.h"
#include "RayCastingComponent.generated.h"

/**
 * @brief 射线检测组件
 */
UCLASS(Blueprintable, Abstract, ClassGroup = (RayCastingComponent))
class PHOBIA_API URayCastingComponent : public UCharacterComponent
{
	GENERATED_BODY()

public:
	URayCastingComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief 检测是否捕获到可交互物体，如果捕获到，则使执行物体被检测逻辑
	 * @param Direction 检测方向
	 */
	UFUNCTION(BlueprintCallable, Category = "RayCasting")
	void CastActor(const FVector& Direction);

private:
	// 射线检测距离
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RayCasting", meta = (AllowPrivateAccess = "true"))
	float RayCastingDistance;

	// 碰撞参数
	FCollisionQueryParams CollisionQueryParams;
	// 捕获对象
	AActor* BeCastActor;
};
