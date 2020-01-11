// Copyright Dalton Lima 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("[OpenDoor] BeginPlay @ %s - TargetYaw: %f"), *GetOwner()->GetName(), TargetYaw);

	ClosedRotation = GetOwner()->GetActorRotation();
	OpenRotation = ClosedRotation;
	OpenRotation.Add(0.f, 90.f, 0.f);
	//OpenDoor();
}

void UOpenDoor::OpenDoor() const
{
	
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation = FMath::Lerp(CurrentRotation, OpenRotation, 0.02f);

	GetOwner()->SetActorRotation(CurrentRotation);
}

