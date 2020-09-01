// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include <Components/InputComponent.h>
#include "Grabbing_Component.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TEAM09_DARKLIGHT_API UGrabbing_Component : public UActorComponent
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
private:

	UPROPERTY(EditAnywhere, Category = "Grab Distance")
		float Reach = 100.f;

	UPROPERTY(EditAnywhere, Category = "Drag Helper Value") //smoothing grabbing function
		float UpdateLocationHelper = 10.f;


	FHitResult GetObjectInReach();
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;


};