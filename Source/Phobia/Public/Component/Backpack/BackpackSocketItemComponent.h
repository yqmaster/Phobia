#pragma once

#include "CoreMinimal.h"
#include "BackpackSocketItemComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Utility, Common), Blueprintable, hideCategories=(Trigger, PhysicsVolume), meta=(ShortTooltip="挂在它下面的Component不要动旋转跟位置!!!"))
class PHOBIA_API UBackpackSocketItemComponent : public USceneComponent
{
	GENERATED_BODY()
};
