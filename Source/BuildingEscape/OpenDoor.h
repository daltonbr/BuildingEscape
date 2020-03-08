// Copyright Dalton Lima 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(const float DeltaTime);
	void CloseDoor(const float DeltaTime);
	float TotalMassOfActors() const;

protected:	
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly)
	UCurveFloat* YawCurve = nullptr;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;

	UPROPERTY(EditAnywhere)
	// Time used to extend the opening of the door
	float OpeningDuration = 3.5f;

 //    UPROPERTY(EditAnywhere)
	// float ClosingDuration = 1.0f;

    UPROPERTY(EditAnywhere)
	float DoorCloseDelayInSeconds = 2.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	FRotator InitialRotation;

	bool bIsOpen;
	bool bIsClosed;
	float ElapsedTime;
	float DoorLastOpened = 0.f;
};
