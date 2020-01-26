// Copyright Dalton Lima 2020


#include "Grabbable.h"

// Add default functionality here for any IGrabbable functions that are not pure virtual.
void IGrabbable::PickedUp()
{
    UE_LOG(LogTemp, Warning, TEXT("Item %s weighting %d kilos, was grabbed!"), *ItemName, Weight);
}

void IGrabbable::PickedUp2()
{
}
