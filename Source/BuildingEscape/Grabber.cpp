// Copyright Dalton Lima 2020

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
//#include "CollisionQueryParams.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	PlayerController = GetWorld()->GetFirstPlayerController();

	// Check for PhysicsHandleComponent
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UPhysicsHandleComponent attached to %s"), *GetOwner()->GetName());
	}
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

	// Get the End Position
	FVector const LineTraceDirection = PlayerViewPointRotation.Vector();
	FVector const LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * Reach);

	// Ray-cast out to a certain distance (Reach private member variable)
	DrawDebugLine(GetWorld(),
		PlayerViewPointLocation, LineTraceEnd,
		FColor::Red,
		false, -1, 0, 4
	);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(
		FName(TEXT("")),
		false,
		GetOwner()
	);	

    bool Hit = GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	if (Hit)
	{
		FString HitName = HitResult.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("We hit: %s"), *HitName);
	}	

	// FindComponentByClass()

	// <> for generics
	// nullptr to initialise pointers
	// log a useful error if the component isn't attached, specifically a PhysicsHandle

}

