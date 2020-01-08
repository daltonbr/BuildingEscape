// Copyright Dalton Lima 2020

#include "WorldPosition.h"
#include "GameFramework/Actor.h"
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

void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	const auto Owner = UActorComponent::GetOwner();
	const auto Name = Owner->GetName();
	auto WorldPosition = Owner->GetTransform().GetLocation();

	UE_LOG(LogTemp, Warning, TEXT("[WorldPosition] %s @ %s"), *Name, *WorldPosition.ToCompactString());
}

void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
