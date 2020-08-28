// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"
#include "PuzzleKey.h"
#include "Team09_DarkLight\RealmType.h"
#include "PuzzleType.h"
#include "Components/BoxComponent.h"

#include "PuzzleActor.generated.h"

UCLASS()
class TEAM09_DARKLIGHT_API APuzzleActor : public AActor, public IPuzzle
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleActor();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* TriggerBox = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		TEnumAsByte<RealmType> VisibleRealm = RealmType::Dark;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		TEnumAsByte<RealmType> TypeOfSoul = RealmType::Dark;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		int TotalSoulsNeeded = 1;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Puzzle")
		int TotalSoulsTurnedIn = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		AActor* GateToOpen = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		TArray<AActor*> LiftableObjects;

private:
	TArray<IPuzzleKey*> Keys;
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

};
