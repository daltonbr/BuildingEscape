// Copyright Dalton Lima 2020

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
//#include "DrawDebugHelpers.h"
//#include "CollisionQueryParams.h"

#define OUT

UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	FindPhysicsHandle();
	SetupInputComponent();		
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	    // Move the object we are holding
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("[Grabber] Grab Pressed"));

	// only raycast when key is pressed. (maybe not if we want a different behaviour)
	FHitResult hit = GetFirstPhysicsBodyInReach();

	// Try and reach any actors with physics body collision channel set.

	// If we hit something then attach the physics handle.

	//TODO: attach the physics handle

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("[Grabber] Grab Released"));

    //TODO: remove/release the physics handle.
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UPhysicsHandleComponent attached to %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	// This component is always embedded
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent couldn't be found on %s"), *GetOwner()->GetName());
	}

	InputComponent->BindAction(GrabActionName, EInputEvent::IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction(GrabActionName, EInputEvent::IE_Released, this, &UGrabber::Release);
}

// Returns the first Actor within reach with physics body
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
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
	//DrawDebugLine(GetWorld(),
	//	PlayerViewPointLocation,
	//	LineTraceEnd,
	//	FColor::Red,
	//	false, -1, 0, 4
	//);

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
		UE_LOG(LogTemp, Warning, TEXT("[Grabber] We hit: %s"), *HitName);
	}
	return HitResult;
}

