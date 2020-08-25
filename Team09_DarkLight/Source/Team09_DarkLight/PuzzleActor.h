// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"
#include "PuzzleKey.h"
#include "PuzzleActor.generated.h"

UCLASS()
class TEAM09_DARKLIGHT_API APuzzleActor : public AActor, public IPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleActor();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TScriptInterface<IPuzzleKey>>  PuzzleKeys;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetKeysToSolve(int TotalKeys) override;


	void TryToSolveWithKeys() override;


	void OnSolved() override;

};
