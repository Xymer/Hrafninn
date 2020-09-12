// Fill out your copyright notice in the Description page of Project Settings.
#include "ASoulFollowTargetComponent.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Math/TransformNonVectorized.h"
#include "Math/Vector.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UASoulFollowTargetComponent::UASoulFollowTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UASoulFollowTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	refDistanceFromPlayerZ = distanceFromPlayerZ;
	currentDistanceFromPlayerZ = 0.0f;
	tempSpawnSwayPos = this->GetOwner()->GetActorLocation();
}

/*
void UASoulFollowTargetComponent::LineTrace()
{
	FVector startLoc = this->GetOwner()->GetActorLocation();
	FVector endLoc = targetLocation;

	FHitResult lineHits;
	FCollisionQueryParams lineParams;

	GetWorld()->LineTraceSingleByChannel(lineHits, startLoc, endLoc, ECC_Visibility, lineParams);
	//DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, false, 2.0f);

	float lineDistance = this->GetOwner()->GetDistanceTo(TargetFollow);
	lineDistance = FMath::Clamp(lineDistance, 0.5f, 8.0f);


	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(lineDistance));
	//Acceleration(lineDistance);

}


void UASoulFollowTargetComponent::RotationCorrection(FVector vector1, FVector vector2)
{
	playerDirection = TargetFollow->GetActorRotation().Yaw;
	//playerDirection = FVector::DotProduct(vector1, vector2);
	//playerDirection = FMath::Clamp(playerDirection, -1.0f, 1.0f);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(playerDirection));
}
*/

void UASoulFollowTargetComponent::MoveOrb()
{
	if (TargetFollow) {
		
		targetLocation = TargetFollow->GetRootComponent()->GetComponentLocation() +=
			TargetFollow->GetActorForwardVector() * -distanceFromPlayerX +=
			TargetFollow->GetActorUpVector() * currentDistanceFromPlayerZ
			+= TargetFollow->GetActorRightVector() * distanceFromPlayerY;
		
		tempLoc = FMath::VInterpTo(tempLoc, targetLocation, GetWorld()->DeltaTimeSeconds, orbDrag * orbAcceleration);
		this->GetOwner()->SetActorLocation(tempLoc);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ORB CANT FOLLOW TARGET, 'Target Follow' IS MISSING"));
		else
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("GEngine not loaded, cant print error"));
	}
}

void UASoulFollowTargetComponent::OrbVerticalSway()
{
	if (isOrbActive == false)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::SanitizeFloat(this->GetOwner()->GetActorLocation().Z));
		FVector currentPos = this->GetOwner()->GetActorLocation();
		FVector targetVector = this->GetOwner()->GetActorLocation();
		targetVector.Z *= currentDistanceFromPlayerZ;
		if (bGoUp)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("up"));
			currentDistanceFromPlayerZ = FMath::FInterpTo(currentDistanceFromPlayerZ, tempSpawnSwayPos.Z + orbUpSwayHeight, GetWorld()->DeltaTimeSeconds, orbUpSwaySpeed / 2);
			wishPos = FMath::VInterpConstantTo(currentPos, targetVector, GetWorld()->DeltaTimeSeconds, orbUpSwaySpeed / 2);
			//wishPos = FMath::VInterpTo(currentPos, targetVector, GetWorld()->DeltaTimeSeconds, orbUpSwaySpeed / 2);
			if (wishPos.Z >= tempSpawnSwayPos.Z + orbUpSwayHeight)
				bGoUp = false;
		}
		else if (!bGoUp)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("down"));
			currentDistanceFromPlayerZ = FMath::FInterpTo(currentDistanceFromPlayerZ, -tempSpawnSwayPos.Z, GetWorld()->DeltaTimeSeconds, orbUpSwaySpeed / 2);
			wishPos = FMath::VInterpConstantTo(currentPos, targetVector, GetWorld()->DeltaTimeSeconds, orbUpSwaySpeed / 2);
			//wishPos = FMath::VInterpTo(currentPos, targetVector, GetWorld()->DeltaTimeSeconds, orbUpSwaySpeed / 2);
			if (wishPos.Z <= tempSpawnSwayPos.Z)
				bGoUp = true;
		}
		this->GetOwner()->SetActorLocation(wishPos);
	}
		else {
			if (bGoUp) {
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("up"));

				// currentDistanceFromPlayerZ = FMath::FInterpTo(currentDistanceFromPlayerZ, distanceFromPlayerZ + orbUpSwayHeight, GetWorld()->DeltaTimeSeconds * 2.0f, orbUpSwaySpeed);
				currentDistanceFromPlayerZ = FMath::FInterpConstantTo(currentDistanceFromPlayerZ, distanceFromPlayerZ + orbUpSwayHeight, GetWorld()->DeltaTimeSeconds, orbUpSwaySpeed);
				// currentDistanceFromPlayerZ = FMath::Lerp(currentDistanceFromPlayerZ, distanceFromPlayerZ + orbUpSwayHeight, orbUpSwaySpeed);

				if (currentDistanceFromPlayerZ >= distanceFromPlayerZ + orbUpSwayHeight) {
					bGoUp = false;
				}

			}
			else if (!bGoUp) {
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, TEXT("down"));

				//currentDistanceFromPlayerZ = FMath::FInterpTo(currentDistanceFromPlayerZ, distanceFromPlayerZ - orbUpSwayHeight, GetWorld()->DeltaTimeSeconds * 2.0f, orbUpSwaySpeed);
				currentDistanceFromPlayerZ = FMath::FInterpConstantTo(currentDistanceFromPlayerZ, distanceFromPlayerZ - orbUpSwayHeight, GetWorld()->DeltaTimeSeconds, orbUpSwaySpeed);
				//currentDistanceFromPlayerZ = FMath::Lerp(currentDistanceFromPlayerZ, distanceFromPlayerZ - orbUpSwayHeight, orbUpSwaySpeed);

				if (currentDistanceFromPlayerZ <= distanceFromPlayerZ - orbUpSwayHeight) {
					bGoUp = true;
				}

			}
		}
}

void UASoulFollowTargetComponent::RandomzieTheValues()
{
	//Randomizes the values at the start to give a tiny bit of variation
	distanceFromPlayerX = FMath::RandRange(distanceFromPlayerX - 2, distanceFromPlayerX);
	distanceFromPlayerZ = FMath::RandRange(distanceFromPlayerZ / 2, distanceFromPlayerZ);
	distanceFromPlayerY = FMath::RandRange(-15.0f , 15.0f);
	orbAcceleration = FMath::RandRange(orbAcceleration / 2, orbAcceleration);
	orbUpSwayHeight = FMath::RandRange(orbUpSwayHeight / 2, orbUpSwayHeight);
}

void UASoulFollowTargetComponent::SetUp(AActor* followActor)
{
	PrimaryComponentTick.TickInterval = PrimaryComponentTick.TickInterval / 2;

	if (!TargetFollow) {
		TargetFollow = followActor;	//if there isnt a actor assigned in the component, use the one assigned in bp
		if (TargetFollow) {
			tempLoc = this->GetOwner()->GetActorLocation();
			currentDistanceFromPlayerZ = 0;
			RandomzieTheValues();
			isOrbActive = true;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("IsOrbActive IS TRUE NOW"));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ERROR Target Follow is NULL"));
		}
	}
}

void UASoulFollowTargetComponent::SoulTurnedIn_Implementation(AActor* lanternActor)
{
	isOrbActive = false;
/*	if (lanternActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Monkey Flip"));
	}
	
	FTimerHandle delayTimer;
	FVector lantLoc = lanternActor->GetActorLocation();

	tempLoc = FMath::VInterpConstantTo(tempLoc, lantLoc, GetWorld()->DeltaTimeSeconds, 1.0f);
	this->GetOwner()->SetActorLocation(tempLoc);
	GetWorld()->GetTimerManager().SetTimer(delayTimer, this, &UASoulFollowTargetComponent::DestroyObj,1.0f);
*/	
}

void UASoulFollowTargetComponent::DestroyObj()
{
	//this->GetOwner()->Destroy(false, false);
}

// Called every frame
void UASoulFollowTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	OrbVerticalSway(); 
	if (isOrbActive) {
		//LineTrace();
		MoveOrb();
		//OrbVerticalSway();
	}
}
