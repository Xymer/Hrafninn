// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Team09_DarkLight\PuzzleKeyActor.h>
#include "Team09_DarkLightCharacter.generated.h"

UCLASS(config = Game)
class ATeam09_DarkLightCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	TArray<APuzzleKeyActor*> HeldKeys;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	void MoveUp(float Val);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	ATeam09_DarkLightCharacter();

	void PickUpKey(APuzzleKeyActor* KeyToPickup);

};
