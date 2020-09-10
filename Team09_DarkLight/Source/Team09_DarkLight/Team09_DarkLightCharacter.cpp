// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team09_DarkLightCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Grabbing_Component.h"

ATeam09_DarkLightCharacter::ATeam09_DarkLightCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
}




void ATeam09_DarkLightCharacter::PickUpKey(ASoulActor* KeyToPickup)
{
	if (HeldSouls.Contains(KeyToPickup))
	{
		return;
	}
	HeldSouls.Add(KeyToPickup);
}

void ATeam09_DarkLightCharacter::Jump()
{
	if (HeldItem)
	{
		return;
	}
	if (bIsInAir)
	{
		Execute_OnPressedJump(this);
	}
	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;
}


//////////////////////////////////////////////////////////////////////////
// Input

void ATeam09_DarkLightCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATeam09_DarkLightCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATeam09_DarkLightCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ATeam09_DarkLightCharacter::MoveUp);

}

void ATeam09_DarkLightCharacter::BeginPlay()
{
	Super::BeginPlay();
	FindComponentByClass<UGrabbing_Component>()->SetOwner(this);
}

void ATeam09_DarkLightCharacter::MoveRight(float Value)
{
	if (HeldItem)
	{
		UStaticMeshComponent* tempMesh = HeldItem->FindComponentByClass<UStaticMeshComponent>();

		if (FMath::RoundToInt(FVector::DotProduct(tempMesh->GetRelativeLocation().ForwardVector, GetActorForwardVector())) == 0)
		{
			AddMovementInput(GetActorForwardVector(), Value * HeldItemMoveSpeedMultiplier);
		}
	}
	else
	{
		AddMovementInput(FVector(0.0f, -1.0f, 0.0f), Value);
	}
}

void ATeam09_DarkLightCharacter::MoveUp(float Value)
{
	if (HeldItem)
	{

		UStaticMeshComponent* tempMesh = HeldItem->FindComponentByClass<UStaticMeshComponent>();
		if (FMath::RoundToInt(FVector::DotProduct(tempMesh->GetRelativeLocation().ForwardVector, GetActorForwardVector())) == 1)
		AddMovementInput(GetActorForwardVector(), Value * HeldItemMoveSpeedMultiplier);
	}
	else
	{
		AddMovementInput(FVector(-1.0f, 0.0f, 0.0f), Value);
	}
}


