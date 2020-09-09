// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoulActor.h"
#include "JumpInterface.h"
#include "Team09_DarkLightCharacter.generated.h"

UCLASS(config = Game)
class ATeam09_DarkLightCharacter : public ACharacter, public IJumpInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<ASoulActor*> HeldSouls;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		AActor* HeldItem = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Held Item", meta = (UIMin = 0.0001, UIMax = 1.00))
		float HeldItemMoveSpeedMultiplier = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsInAir = false;

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
