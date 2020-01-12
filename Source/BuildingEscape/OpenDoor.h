// Copyright Dalton Lima 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
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

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditInstanceOnly)
	UCurveFloat* YawCurve;		

	UPROPERTY(EditAnywhere)
	// Time used to extend the opening of the door
	float OpeningDuration = 3.5f;

	FRotator InitialRotation;

	bool bIsOpen;
	float ElapsedTime;
};
