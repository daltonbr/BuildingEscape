// Copyright Dalton Lima 2020

#include "Item.h"

// Sets default values for this component's properties
UItem::UItem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Name = "Test";
}

void UItem::BeginPlay()
{
	Super::BeginPlay();
	PickedUp();
	PickedUp2();
}

void UItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItem::PickedUp2()
{
	UE_LOG(LogTemp, Warning, TEXT("Item %s picked up"), *Name);
}
