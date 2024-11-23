#include "Component/RayCasting/RayCastingComponent.h"

#include "Component/Item/Interface/DetectedItemInterface.h"

/**
 * 捕获后处理
 * @param HitActor 捕获对象
 * @param bDetected 是否被检测
 */
void PostCast(const AActor* HitActor, bool bDetected)
{
	TArray<UActorComponent*> ActorComponents;
	HitActor->GetComponents(UActorComponent::StaticClass(), ActorComponents);
	for (UActorComponent* ActorComponent : ActorComponents)
	{
		if (IDetectedItemInterface* ItemInterface = Cast<IDetectedItemInterface>(ActorComponent))
		{
			ItemInterface->OnDetected(bDetected);
		}
	}
}

URayCastingComponent::URayCastingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	CollisionQueryParams.AddIgnoredActor(GetOwner());
}


// Called when the game starts
void URayCastingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URayCastingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CastActor();
}

void URayCastingComponent::CastActor()
{
	// 定义射线
	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector EndLocation = StartLocation + GetOwner()->GetActorForwardVector() * RayCastingDistance;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, CollisionQueryParams);

	if (AActor* HitActor = HitResult.GetActor())
	{
		
		if (HitActor == BeCastActor)
		{
			return;
		}
		
		if (BeCastActor)
		{
			PostCast(BeCastActor, false);
		}

		PostCast(HitActor, true);
		BeCastActor = HitActor;
	}
	else if (BeCastActor)
	{
		PostCast(BeCastActor, false);
		BeCastActor = nullptr;
	}
}

