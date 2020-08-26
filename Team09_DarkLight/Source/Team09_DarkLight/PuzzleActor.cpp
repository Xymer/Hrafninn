// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleActor.h"
#include <Math/Color.h>

// Sets default values
APuzzleActor::APuzzleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APuzzleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleActor::SetKeysToSolve()
{	
	for (int i = 0; i < PuzzleKeys.Num(); i++)
	{
		IPuzzleKey* Key = Cast<IPuzzleKey>(PuzzleKeys[i]);
		if (Key != NULL)
		{
		Keys.Add(Key);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3, FColor::Blue, PuzzleKeys[i]->GetFName().ToString() + " Is not a valid key");
		}
	}
}

void APuzzleActor::TryToSolveWithKeys(APawn* pawn)
{
 
}

void APuzzleActor::OnSolved()
{
	throw std::logic_error("The method or operation is not implemented.");
}

