// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include <Components/InputComponent.h>
#include "Team09_DarkLightCharacter.h"
#include "GrabbableInterface.h"
#include "Grabbing_Component.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TEAM09_DARKLIGHT_API UGrabbing_Component : public UActorComponent, public IGrabbableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabbing_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void InputHandling();
	void CheckForPhysicsHandler();



public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateGrabbedItemLocation();

	void PushPull();
	void StopPushPull();
	void SetOwner(ATeam09_DarkLightCharacter* Owner);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Held Item", meta = (UIMin = 0.0001, UIMax = 750.00))
		float HeldItemAccelerationAdjust = 100.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Held Item")
		float DistanceToReleaseObject = 50.0f;
	AActor* CurrentOwner = nullptr;
	FVector StartLineTrace;
	FVector EndofLineTrace;
	FVector ExtensionFromStartLineTrace;
	FRotator RotatelineTrace;
	UPrimitiveComponent* GrabbedItemComponent;
	float distance = 0;
private:

	UPROPERTY(EditAnywhere, Category = "Grab Distance")
		float Reach = 100.f;

	UPROPERTY(EditAnywhere, Category = "Push Helper Value")
		float distanceOffset = 10;
	ATeam09_DarkLightCharacter* Player = nullptr;

	FHitResult GetObjectInReach();
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

};