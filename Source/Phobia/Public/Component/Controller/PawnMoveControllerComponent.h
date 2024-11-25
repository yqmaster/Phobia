#pragma once

#include "CoreMinimal.h"
#include "PlayerController/PlayerControllerComponent.h"
#include "PawnMoveControllerComponent.generated.h"

class UInputAction;
struct FInputActionValue;
class UPawnMoveComponent;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (ControllerComponent))
class PHOBIA_API UPawnMoveControllerComponent : public UPlayerControllerComponent
{
	GENERATED_BODY()

protected:
	virtual void OnSetupInputComponent(UEnhancedInputComponent* InInputComponent) override;
	virtual void OnPossessed(ACharacter* InCharacter) override;
	virtual void OnUnPossessed() override;

	void Move(const FInputActionValue& InValue);
	void StartRush(const FInputActionValue& InValue);
	void EndRush(const FInputActionValue& InValue);

private:
	void CachePawnMoveComponent();
	void UnCachePawnMoveComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* RushAction = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, Transient, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPawnMoveComponent> PawnMoveComponent = nullptr;
};
