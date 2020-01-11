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
	UE_LOG(LogTemp, Warning, TEXT("[OpenDoor] BeginPlay @ %s"), *GetOwner()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("[WorldPosition] %s @ %s"), *Name, *WorldPosition.ToCompactString());

	OpenDoor();
}

void UOpenDoor::OpenDoor() const
{
	float Angle = 90.f;
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = Angle;
	GetOwner()->SetActorRotation(CurrentRotation);	
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

