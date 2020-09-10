// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ASoulFollowTargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM09_DARKLIGHT_API UASoulFollowTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASoulFollowTargetComponent();

	UPROPERTY(EditAnywhere, Category = "Soul Follow")
		AActor* TargetFollow;

	UPROPERTY()
		FVector tempLoc;

	UPROPERTY()
		FVector targetLocation;

	UPROPERTY()
		FVector lanternLocation;

	UPROPERTY()
		FRotator tempRot;

	UPROPERTY()
		FRotator targetRotation;

	UPROPERTY(EditAnywhere, Category = "Soul Follow")
		float distanceFromPlayerX = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Soul Follow")
		float distanceFromPlayerZ = 50.0f;

	float refDistanceFromPlayerZ;

	float currentDistanceFromPlayerZ;

	float distanceFromPlayerY = 0;

	UPROPERTY(EditAnywhere, Category = "Soul Follow")
		float orbUpSwayHeight = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Soul Follow")
		float orbUpSwaySpeed = 15.0f;

	UPROPERTY(EditAnywhere, Category = "Soul Follow")
		float orbDrag = 2.2f;

		float orbAcceleration = 1.0f;

		float playerDirection = 0.0f;

		bool isOrbActive = false;

		bool bGoUp = false;

		FVector tempSpawnSwayPos;

		FVector wishPos;

public:	
	

	UFUNCTION()
		void Acceleration(float lineLenght);

	//UFUNCTION()
	//	void LineTrace();

//	UFUNCTION(BlueprintCallable, Category = "SoulFollowComponent")
//		void RotationCorrection(FVector vector1, FVector vector2);

	UFUNCTION(BlueprintCallable, Category = "SoulFollowComponent")
		void MoveOrb();

	UFUNCTION(BlueprintCallable, Category = "SoulFollowComponent")
		void OrbVerticalSway();

	UFUNCTION()
		void RandomzieTheValues();

	UFUNCTION(BlueprintCallable, Category = "SoulFollowComponent")
		void SetUp(AActor* followActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SoulFollowComponent")
		void SoulTurnedIn(AActor* lanternActor);

	void DestroyObj();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;
		
};
