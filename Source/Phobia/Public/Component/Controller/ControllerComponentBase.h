#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ControllerComponentBase.generated.h"

class APCharacterBase;
class APPlayerController;

UCLASS(BlueprintType, abstract, ClassGroup = (ControllerComponent))
class PHOBIA_API UControllerComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Controller 调用, 用于初始化输入组件
	void SetupInputComponent(UEnhancedInputComponent* InInputComponent);
	// Controller 调用, 用于发送开始控制角色的事件
	void PossessCharacter(APlayerController* InPlayerController, APCharacterBase* InCharacter);
	// Controller 调用, 用于发送结束控制角色的事件
	void UnPossessCharacter();

protected:
	// C++ 内部实现: 当输入组件初始化
	virtual void OnSetupInputComponent(UEnhancedInputComponent* InInputComponent) {}

	// 蓝图 内部实现: 当输入组件初始化
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Setup Input Component", ForceFunctionOverwrite))
	void ReceiveOnSetupInputComponent(UEnhancedInputComponent* InInputComponent);

	// C++ 内部实现: 当控制器开始控制角色时
	virtual void OnPossessed(APCharacterBase* InCharacter) {}

	// C++ 内部实现: 当控制器结束控制角色时
	virtual void OnUnPossessed() {}

	// 蓝图 内部实现: 当控制器的控制对象发生变化时
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPossessedPawnChange"))
	void ReceiveOnPossessed(APCharacterBase* InCharacter);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPossessedPawnChange"))
	void ReceiveOnUnPossessed();

	// ControllerComponent 组件获取增强输入组件
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEnhancedInputComponent* GetInputComponent() const;

	// ControllerComponent 组件获取 PlayerController
	UFUNCTION(BlueprintCallable, BlueprintPure)
	APPlayerController* GetPlayerController() const;

	// ControllerComponent 组件获取控制的角色
	UFUNCTION(BlueprintCallable, BlueprintPure)
	APCharacterBase* GetControlledCharacter() const;

private:
	UPROPERTY(Transient)
	TObjectPtr<APCharacterBase> CachedPlayerCharacter = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UEnhancedInputComponent> CachedInputComponent = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<APPlayerController> CachedPlayerController = nullptr;
};
