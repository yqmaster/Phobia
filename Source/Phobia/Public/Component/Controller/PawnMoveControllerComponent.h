#pragma once

#include "CoreMinimal.h"
#include "Component/Controller/ControllerComponentBase.h"
#include "PawnMoveControllerComponent.generated.h"

class UInputAction;
struct FInputActionValue;
class UPawnMoveComponent;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (ControllerComponent))
class PHOBIA_API UPawnMoveControllerComponent : public UControllerComponentBase
{
	GENERATED_BODY()

protected:
	virtual void OnSetupInputComponent(UEnhancedInputComponent* InInputComponent) override;
	virtual void OnPossessed(APCharacterBase* InCharacter) override;
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
