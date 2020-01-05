// Copyright Dalton Lima 2020

#include "WorldPosition.h"
#include "Engine/Engine.h"

#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green,text)

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("[WorldPosition] Demo Display"));
	UE_LOG(LogTemp, Warning, TEXT("[WorldPosition] Demo Warning"));
	UE_LOG(LogTemp, Error, TEXT("[WorldPosition] Demo Error"));
	// ...
	PRINT("hello macro!");
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

