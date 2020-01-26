// Copyright Dalton Lima 2020

#pragma once

#include "CoreMinimal.h"
#include "Grabbable.h"
#include "Components/ActorComponent.h"
#include "Item.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UItem : public UActorComponent, public IGrabbable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PickedUp2() override;

private:
	UPROPERTY(EditAnywhere)
	FString Name;
};
