#include "Component/Controller/ControllerComponentBase.h"
#include "3C/Controller/PPlayerController.h"

UControllerComponentBase::UControllerComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UControllerComponentBase::BeginPlay()
{
	Super::BeginPlay();

	APPlayerController* Controller = Cast<APPlayerController>(GetOwner());
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] is a PPlayerController's Component, [%s] is not PPlayerController"), *GetName(), *GetOwner()->GetName());
		return;
	}

	PlayerController = Controller;
	PlayerController->OnPossessedPawnChanged.AddDynamic(this, &UControllerComponentBase::OnPossessedPawnChange);
}

void UControllerComponentBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerController)
	{
		PlayerController->OnPossessedPawnChanged.RemoveDynamic(this, &UControllerComponentBase::OnPossessedPawnChange);
	}

	PlayerController = nullptr;

	Super::EndPlay(EndPlayReason);
}

void UControllerComponentBase::OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn)
{

}