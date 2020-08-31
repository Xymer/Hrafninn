// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulInterface.h"
#include "RealmType.h"
#include "Components/BoxComponent.h"
#include "RealmObject.h"
#include "SoulActor.generated.h"

UCLASS()
class TEAM09_DARKLIGHT_API ASoulActor : public AActor, public ISoulInterface,public IRealmObject
{
	GENERATED_BODY()
private:
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
public:
	// Sets default values for this actor's properties
	ASoulActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Realm")
		TEnumAsByte<RealmType> VisibleRealm = RealmType::Dark;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Realm")
		TEnumAsByte<RealmType> TypeOfSoul = RealmType::Dark;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UBoxComponent* BoxComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Realm")
		bool bIsAffectedByRealm = true;
	bool bIsPickedUp = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
