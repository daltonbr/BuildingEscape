// Copyright Dalton Lima 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Grabbable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGrabbable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUILDINGESCAPE_API IGrabbable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    int32 Weight;
    FString ItemName;

    void PickedUp();
    virtual void PickedUp2();
};
