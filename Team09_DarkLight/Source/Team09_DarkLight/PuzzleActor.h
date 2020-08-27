// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"
#include "PuzzleKey.h"
#include "Team09_DarkLight\RealmType.h"
#include "PuzzleType.h"
#include "PuzzleActor.generated.h"

UCLASS()
class TEAM09_DARKLIGHT_API APuzzleActor : public AActor, public IPuzzle
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		TArray<AActor*>  PuzzleKeys;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Puzzle")
		TEnumAsByte<RealmType> TypeOfRealm = RealmType::Dark;

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


	void TryToSolveWithKeys(APawn* pawn) override;


	void OnSolved() override;

};
