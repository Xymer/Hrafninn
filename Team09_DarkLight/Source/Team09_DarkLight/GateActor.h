// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GateInterface.h"
#include "GateActor.generated.h"

UCLASS()
class TEAM09_DARKLIGHT_API AGateActor : public AActor, public IGateInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGateActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Door")
		bool bIsOpen = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void OpenDoor() override;

	UFUNCTION(BlueprintCallable)
	void CloseDoor() override;

};
