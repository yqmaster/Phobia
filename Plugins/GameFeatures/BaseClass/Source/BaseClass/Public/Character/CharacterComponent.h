#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterComponent.generated.h"

class ACharacter;
class UCharacterMovementComponent;
class UCameraComponent;

UCLASS(Blueprintable, Abstract, Config = Engine)
class BASECLASS_API UCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// 获取组件对应的 角色
	UFUNCTION(Blueprintable, BlueprintPure)
	ACharacter* GetOwnerCharacter() const;

	// 获取组件对应的 角色移动组件
	UFUNCTION(Blueprintable, BlueprintPure)
	UCharacterMovementComponent* GetCharacterMovementComponent() const;

	// 获取组件对应的 角色摄像机组件
	UFUNCTION(Blueprintable, BlueprintPure)
	UCameraComponent* GetCameraComponent() const;

private:
	UPROPERTY(Transient)
	TObjectPtr<ACharacter> CachedCharacter = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UCharacterMovementComponent> CachedMovementComponent = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UCameraComponent> CachedCameraComponent = nullptr;
};
