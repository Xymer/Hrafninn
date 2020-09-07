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


void UASoulFollowTargetComponent::Acceleration(float lineLenght)
{
	orbAcceleration = lineLenght;
}

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


void UASoulFollowTargetComponent::MoveOrb()
{
	if (TargetFollow) {
	
		//DistanceCorrection(this->GetOwner()->GetActorLocation(), targetLocation);
		//targetLocation = TargetFollow->GetRootComponent()->GetComponentLocation() += FVector::ForwardVector * distanceFromPlayer;
		targetLocation = TargetFollow->GetRootComponent()->GetComponentLocation() +=
			TargetFollow->GetActorForwardVector() * -distanceFromPlayerX +=
			TargetFollow->GetActorUpVector() * distanceFromPlayerZ
			+= TargetFollow->GetActorRightVector() + distanceFromPlayerY;
		//targetLocation.Y = TargetFollow->GetRootComponent()->GetComponentLocation().Y + distanceFromPlayerY;
		//targetLocation.X = FMath::Clamp(targetLocation.X, -5.0f, 5.0f);
		//targetLocation.Y = FMath::Clamp(targetLocation.Y, -5.0f, 5.0f);

		//DrawDebugPoint(GetWorld(), targetLocation, 5, FColor::Red, false, 0.0f);
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
	/*if (isOrbActive == false)	wip
	{
		tempDistanceFromPlayerZ = this->GetOwner()->GetActorLocation().Z;
		this->GetOwner()->SetActorLocation().Z = tempDistanceFromPlayerZ;
	}*/
		if (bGoUp) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("up"));

			distanceFromPlayerZ = FMath::FInterpTo(distanceFromPlayerZ, distanceFromPlayerZ + orbZSwayMax, GetWorld()->DeltaTimeSeconds  * orbZSwayAcceleration, orbZSwaySpeed);

			if (distanceFromPlayerZ > tempDistanceFromPlayerZ + orbZSwayMax) {
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SWITCH"));
				timeCheck = 0.0f;
				bGoUp = false;
			}
	
		}
		else if (!bGoUp) {
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("down"));

			distanceFromPlayerZ = FMath::FInterpTo(distanceFromPlayerZ, distanceFromPlayerZ - orbZSwayMax, GetWorld()->DeltaTimeSeconds * orbZSwayAcceleration, orbZSwaySpeed);

			if (distanceFromPlayerZ < -tempDistanceFromPlayerZ + orbZSwayMax + 50.0f) {
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SWITCH"));
				timeCheck = 0.0f;
				bGoUp = true;
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

	orbZSwayMax = FMath::RandRange(orbZSwayMax / 2, orbZSwayMax);
}

void UASoulFollowTargetComponent::SetUp(AActor* followActor)
{
	if (!TargetFollow) {
		TargetFollow = followActor;	//if there isnt a actor assigned in the component, use the one assigned in bp
		if (TargetFollow) {
			tempLoc = this->GetOwner()->GetRootComponent()->GetComponentLocation();
			isOrbActive = true;
			tempDistanceFromPlayerZ = distanceFromPlayerZ;
			RandomzieTheValues();
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
	//OrbVerticalSway(); wip
	if (isOrbActive) {
		//LineTrace();
		MoveOrb();
		OrbVerticalSway();
	}
}

