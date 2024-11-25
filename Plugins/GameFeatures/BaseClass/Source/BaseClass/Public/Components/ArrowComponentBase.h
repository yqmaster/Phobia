#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "ArrowComponentBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, hidecategories=(Object,LOD,Physics,Lighting,TextureStreaming,Activation,"Components|Activation",Collision), editinlinenew)
class BASECLASS_API UArrowComponentBase : public UArrowComponent
{
	GENERATED_BODY()
};
