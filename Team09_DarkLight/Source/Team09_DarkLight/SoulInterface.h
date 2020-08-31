// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SoulInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USoulInterface : public UInterface
{
	GENERATED_BODY()
};

class TEAM09_DARKLIGHT_API ISoulInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Puzzle Key")
		void OnPickedUp(APawn* Pawn);
	void OnPickedUp_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Puzzle Key")
		void OnDropped();
	void OnDropped_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Puzzle Key")
		void OnTurnIn(AActor* Lantern);
	void OnTurnIn_Implementation();
};
