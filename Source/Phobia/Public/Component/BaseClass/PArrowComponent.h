#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "PArrowComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, hidecategories=(Object,LOD,Physics,Lighting,TextureStreaming,Activation,"Components|Activation",Collision), editinlinenew)
class PHOBIA_API UPArrowComponent : public UArrowComponent
{
	GENERATED_BODY()
};
