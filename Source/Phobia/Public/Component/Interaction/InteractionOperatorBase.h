#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionConfigBase.h"
#include "InteractionOperatorBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, abstract, EditInlineNew, ClassGroup = (Interaction))
class PHOBIA_API UInteractionOperatorBase : public UInteractionConfigBase
{
	GENERATED_BODY()
	
};
