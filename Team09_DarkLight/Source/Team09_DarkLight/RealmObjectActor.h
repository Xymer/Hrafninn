// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealmType.h"
#include "RealmObject.h"
#include "RealmObjectActor.generated.h"

UCLASS()
class TEAM09_DARKLIGHT_API ARealmObjectActor : public AActor, public IRealmObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARealmObjectActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<RealmType> VisibleRealm = RealmType::Light;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


};
