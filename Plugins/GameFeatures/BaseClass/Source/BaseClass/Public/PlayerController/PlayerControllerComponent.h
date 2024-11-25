#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerControllerComponent.generated.h"

class UEnhancedInputComponent;

UCLASS(Blueprintable, Abstract, Config = Engine)
class BASECLASS_API UPlayerControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// PlayerController 调用, 用于初始化输入组件
	void SetupInputComponent(UEnhancedInputComponent* InInputComponent);
	// PlayerController 调用, 用于发送开始控制角色的事件
	void PossessCharacter(APlayerController* InPlayerController, ACharacter* InCharacter);
	// PlayerController 调用, 用于发送结束控制角色的事件
	void UnPossessCharacter();

protected:
	// 内部实现: 当输入组件初始化
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSetupInputComponent"))
	void ReceiveOnSetupInputComponent(UEnhancedInputComponent* InInputComponent);
	virtual void OnSetupInputComponent(UEnhancedInputComponent* InInputComponent) {}

	// 内部实现: 当控制器的控制对象发生变化时
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPossessedPawnChange"))
	void ReceiveOnPossessed(ACharacter* InCharacter);
	virtual void OnPossessed(ACharacter* InCharacter) {}

	// 内部实现: 当控制器结束控制角色时
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPossessedPawnChange"))
	void ReceiveOnUnPossessed();
	virtual void OnUnPossessed() {}

	// 内部使用: 获取增强输入组件
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEnhancedInputComponent* GetInputComponent() const;

	// 内部使用: 获取 PlayerController
	UFUNCTION(BlueprintCallable, BlueprintPure)
	APlayerController* GetPlayerController() const;

	// 内部使用: 获取控制的角色
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACharacter* GetControlledCharacter() const;

private:
	UPROPERTY(Transient)
	TObjectPtr<ACharacter> CachedPlayerCharacter = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UEnhancedInputComponent> CachedInputComponent = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<APlayerController> CachedPlayerController = nullptr;
};
