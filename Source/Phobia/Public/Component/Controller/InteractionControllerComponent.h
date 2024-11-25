#pragma once

#include "CoreMinimal.h"
#include "PlayerController/PlayerControllerComponent.h"
#include "InteractionControllerComponent.generated.h"

enum class EInteractionRoleType : uint8;
class UInteractionPlayerComponent;
class UInputAction;
struct FInputActionValue;

USTRUCT(BlueprintType)
struct PHOBIA_API FStartPressKeyInfo
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	FTimerHandle TimerHandle;

	UPROPERTY(Transient)
	bool bIsFire = false;
};

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (ControllerComponent))
class PHOBIA_API UInteractionControllerComponent : public UPlayerControllerComponent
{
	GENERATED_BODY()

protected:
	virtual void OnSetupInputComponent(UEnhancedInputComponent* InInputComponent) override;
	virtual void OnPossessed(ACharacter* InCharacter) override;
	virtual void OnUnPossessed() override;

private:
	// 绑定按键
	void BindKey(UEnhancedInputComponent* InInputComponent, const EInteractionRoleType InRole, const UInputAction* InAction);
	// 缓存交互组件
	void CacheInteractionComponent();
	// 取消缓存交互组件
	void UnCacheInteractionComponent();
	// 开始按键
	void StartPressKey(EInteractionRoleType InRole);
	// 结束按键
	void EndPressKey(EInteractionRoleType InRole);
	// 按键超时
	void OnTimeOut(EInteractionRoleType InRole);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LeftMouseAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* RightMouseAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PickAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* DropAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PutAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	double ShortPressTime = 0.2;

private:
	UPROPERTY(BlueprintReadOnly, Transient, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractionPlayerComponent> InteractionPlayerComponent = nullptr;

	UPROPERTY(Transient)
	TMap<EInteractionRoleType, FStartPressKeyInfo> PressKeyMap;
};
