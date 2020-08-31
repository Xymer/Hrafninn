// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LanternInterface.h"
#include "SoulInterface.h"
#include "Team09_DarkLight\RealmType.h"
#include "PuzzleType.h"
#include "Components/BoxComponent.h"
#include "RealmObject.h"
#include "GateActor.h"
#include <Components/PointLightComponent.h>
#include "LanternActor.generated.h"

UCLASS()
class TEAM09_DARKLIGHT_API ALanternActor : public AActor, public ILanternInterface, public IRealmObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALanternActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UBoxComponent* TriggerBox = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Realm")
		TEnumAsByte<RealmType> VisibleRealm = RealmType::Dark;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Realm")
		TEnumAsByte<RealmType> TypeOfSoul = RealmType::Dark;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Realm")
		bool bIsAffectedByRealm = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		int TotalSoulsNeeded = 1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Puzzle")
		int TotalSoulsTurnedIn = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		AGateActor* GateToOpen = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		TArray<AActor*> LiftableObjects;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		UPointLightComponent* PointLightComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		float IncreaseIntensityBy = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		float IntensityLerpSpeed = 10;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Puzzle")
		float CurrentIntensity = 0;


private:
	TArray<ISoulInterface*> Keys;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
		void SetKeysToSolve() override;

	UFUNCTION(BlueprintCallable)
		void TryToSolveWithKeys(APawn* pawn) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	void IncreaseIntensity(float Value);
};
