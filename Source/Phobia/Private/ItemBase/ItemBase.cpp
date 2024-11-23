#include "ItemBase/ItemBase.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Misc/MapErrors.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

