// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoulActor.h"
#include "Team09_DarkLightCharacter.generated.h"

UCLASS(config = Game)
class ATeam09_DarkLightCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<ASoulActor*> HeldSouls;

	AActor* HeldItem = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HeldItemMoveSpeedMultiplier = 0.5f;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	void MoveUp(float Val);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

public:
	ATeam09_DarkLightCharacter();
	void PickUpKey(ASoulActor* SoulToPickup);
	void Jump() override;
};
