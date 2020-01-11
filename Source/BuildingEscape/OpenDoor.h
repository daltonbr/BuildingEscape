// Copyright Dalton Lima 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:	
	virtual void BeginPlay() override;
    void OpenDoor() const;

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float LerpDuration = 2.f;	
	const float DeltaYawToOpen = 90.f;
	FRotator InitialRotation;
	FRotator TargetRotation;
};
