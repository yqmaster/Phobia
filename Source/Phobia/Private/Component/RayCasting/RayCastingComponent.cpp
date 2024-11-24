#include "Component/RayCasting/RayCastingComponent.h"

#include "Component/Item/Interface/DetectedItemInterface.h"

/**
 * 捕获后处理
 * @param InOwner 检测发起者
 * @param HitActor 捕获对象
 * @param bDetected 是否被检测
 */
void PostCast(AActor* InOwner, const AActor* HitActor, bool bDetected)
{
	UE_LOG(LogTemp, Log, TEXT("PostCast for [%s], Result [%s]"), *HitActor->GetName(), bDetected ? TEXT("True") : TEXT("False"));
	TArray<UActorComponent*> ActorComponents;
	HitActor->GetComponents(UActorComponent::StaticClass(), ActorComponents);
	for (UActorComponent* ActorComponent : ActorComponents)
	{
		if (ActorComponent->Implements<UDetectedItemInterface>())
		{
			IDetectedItemInterface::Execute_OnDetected(ActorComponent, InOwner, bDetected);
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
}

void URayCastingComponent::CastActor(const FVector& Direction)
{
	AActor* Owner = GetOwner();
	// 定义射线
	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector EndLocation = StartLocation + Direction * RayCastingDistance;

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
			PostCast(Owner, BeCastActor, false);
		}

		PostCast(Owner, HitActor, true);
		BeCastActor = HitActor;
	}
	else if (BeCastActor)
	{
		PostCast(Owner, BeCastActor, false);
		BeCastActor = nullptr;
	}
}
