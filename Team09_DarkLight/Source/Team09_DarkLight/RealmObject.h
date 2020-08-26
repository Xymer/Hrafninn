// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealmObject.generated.h"

UCLASS()
class TEAM09_DARKLIGHT_API ARealmObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARealmObject();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<RealmType> RealmType = RealmType::Light;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
