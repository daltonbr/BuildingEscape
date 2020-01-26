// Copyright Dalton Lima 2020

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	PlayerController = GetWorld()->GetFirstPlayerController();	
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the players viewpoint
	FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
	//PlayerController->GetActorEyesViewPoint(location, rotation);
	PlayerController->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("[Grabber] Location: %s Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString()
 //   );

	// Get the End Position
	FVector LineTraceDirection = PlayerViewPointRotation.Vector();
	FVector LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * Reach);

	// Ray-cast out to a certain distance (Reach private member variable)
	DrawDebugLine(GetWorld(),
		PlayerViewPointLocation, LineTraceEnd,
		FColor::Red,
		false, -1, 0, 4
	);

	// See what it hits


	
	// Use DrawDebugLine()
}

