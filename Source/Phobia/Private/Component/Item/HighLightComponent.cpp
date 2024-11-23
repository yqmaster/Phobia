#include "Component/Item/HighLightComponent.h"

UHighLightComponent::UHighLightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHighLightComponent::BeginPlay()
{
	Super::BeginPlay();
	OnDetected_Implementation(nullptr, false);
}

void UHighLightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHighLightComponent::OnDetected_Implementation(AActor* InOwner, bool bDetected)
{
	TArray<UMeshComponent*> Meshs;
	GetOwner()->GetComponents(UMeshComponent::StaticClass(), Meshs);
	for (UMeshComponent* Mesh : Meshs)
	{
		if (Mesh)
		{
			Mesh->SetRenderCustomDepth(bDetected);
		}
	}
}
