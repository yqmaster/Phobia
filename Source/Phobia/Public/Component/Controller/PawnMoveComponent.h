#pragma once

#include "CoreMinimal.h"
#include "Component/Controller/ControllerComponentBase.h"
#include "PawnMoveComponent.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS(Blueprintable, abstract, ClassGroup = (ControllerComponent))
class PHOBIA_API UPawnMoveComponent : public UControllerComponentBase
{
	GENERATED_BODY()

public:
	UPawnMoveComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	void Move(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
};
