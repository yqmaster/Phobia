#pragma once

#include "CoreMinimal.h"
#include "BackpackInterface.h"
#include "Components/StaticMeshComponent.h"
#include "BackPackItemComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=(Rendering, Common), hidecategories=(Object,Activation,"Components|Activation"), ShowCategories=(Mobility), editinlinenew)
class PHOBIA_API UBackPackItemComponent : public UStaticMeshComponent, public IBackpackInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnAddToBackpack_Implementation(ACharacter* InTarget, AActor* InItem) override;
	virtual void OnRemoveFromBackpack_Implementation(ACharacter* InTarget, AActor* InItem) override;

	virtual void OnSetToHand_Implementation(ACharacter* InTarget, AActor* InItem) override;
	virtual void OnUnSetFromHand_Implementation(ACharacter* InTarget, AActor* InItem) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Backpack")
	float ForceMultiplier = 30.f;
};
