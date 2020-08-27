// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleKey.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UPuzzleKey : public UInterface
{
	GENERATED_BODY()
};

class TEAM09_DARKLIGHT_API IPuzzleKey
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
