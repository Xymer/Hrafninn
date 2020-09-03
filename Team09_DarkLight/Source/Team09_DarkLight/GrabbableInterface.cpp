// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "GrabbableInterface.h"

// Add default functionality here for any IGrabbableInterface functions that are not pure virtual.

void IGrabbableInterface::OnDetectedGrabble_Implementation()
{
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Cyan, FString("Interface Working"), true);
}

void IGrabbableInterface::OnNotDetectedGrabble_Implementation()
{

}


