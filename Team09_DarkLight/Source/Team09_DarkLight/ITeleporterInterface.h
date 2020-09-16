// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITeleporterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UITeleporterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAM09_DARKLIGHT_API IITeleporterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	 void LastSoulTurnedIn();


};
