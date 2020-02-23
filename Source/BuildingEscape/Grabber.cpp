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
	if (PhysicsHandle->GrabbedComponent)
	{
	    // Move the object we are holding

		FVector LineTraceEnd = GetPlayersReach();
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::Grab()
{
	// Try and reach any actors with physics body collision channel set.
	FHitResult hit = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = hit.GetComponent();

	if (hit.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
	        (
			    ComponentToGrab,
			    NAME_None,
				GetPlayersReach()
		    );
	}
}

void UGrabber::Release()
{
    PhysicsHandle->ReleaseComponent();
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
	FHitResult OutHit;
    const FCollisionQueryParams TraceParams(FName(TEXT("")),false,	GetOwner());

	bool Hit = GetWorld()->LineTraceSingleByObjectType(
		OUT OutHit,
		GetPlayersPosition(),
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return OutHit;
}

// Return the position in front of the player, given the Reach distance.
FVector UGrabber::GetPlayersReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	PlayerController->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

FVector UGrabber::GetPlayersPosition() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	PlayerController->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}
