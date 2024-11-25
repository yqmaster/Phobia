#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class UPlayerControllerComponent;
class ACharacter;
class UEnhancedInputComponent;
/**
 * 
 */
UCLASS(Blueprintable, Abstract, Config = Game)
class BASECLASS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	// 获取所有的 PlayerControllerComponent
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UPlayerControllerComponent*> GetPlayerControllerComponents() const;

	// 获取增强输入组件
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEnhancedInputComponent* GetEnhancedInputComponent() const;

	// 获取控制的角色
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACharacter* GetControlledCharacter() const;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void SetupInputComponent() override;
};
