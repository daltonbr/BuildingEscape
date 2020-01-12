// Copyright Dalton Lima 2020

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

#define GAMENAME_DEBUG 1

#if GAMENAME_DEBUG
    #define GAMENAME_CHECK(expr) { if(!(expr)) FDebug::AssertFailed( #expr, __FILE__, __LINE__ ); CA_ASSUME(expr); }
#else
    #define GAMENAME_CHECK(expr)
#endif

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

	GAMENAME_CHECK(YawCurve);

	UE_LOG(LogTemp, Warning, TEXT("[OpenDoor] BeginPlay @ %s"), *GetOwner()->GetName());

	InitialRotation = GetOwner()->GetActorRotation();
	//TargetRotation = InitialRotation;
	//TargetRotation.Add(0.f, DeltaYawToOpen, 0.f);

	ElapsedTime = 0;
	bIsOpen = false;
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	

	if (bIsOpen)
	{
		return;
	}

	if (ElapsedTime > OpeningDuration)
	{
		bIsOpen = true;
		ElapsedTime = 0.f;
		return;
	}

	ElapsedTime += DeltaTime;
	   	
	FRotator CurrentRotation = GetOwner()->GetActorRotation();	

	GAMENAME_CHECK(YawCurve);

	auto CurrentYaw = YawCurve->GetFloatValue(ElapsedTime / OpeningDuration);
	CurrentRotation.Yaw = InitialRotation.Yaw + CurrentYaw;
	GetOwner()->SetActorRelativeRotation(CurrentRotation);
}
