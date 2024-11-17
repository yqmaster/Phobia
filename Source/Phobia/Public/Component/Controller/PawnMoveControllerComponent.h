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

public:
	UPawnMoveControllerComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn) override;

	void Move(const FInputActionValue& Value);
	void StartRush(const FInputActionValue& Value);
	void EndRush(const FInputActionValue& Value);

private:
	void CachePawnMoveComponent(const AActor* InActor);

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<UPawnMoveComponent> PawnMoveComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RushAction;
};
