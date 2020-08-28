// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleActor.h"
#include "Team09_DarkLightCharacter.h"
#include <Math/Color.h>

// Sets default values
APuzzleActor::APuzzleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APuzzleActor::OnOverlapBegin);
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
	
}

void APuzzleActor::TryToSolveWithKeys(APawn* pawn)
{
	ATeam09_DarkLightCharacter* player = Cast<ATeam09_DarkLightCharacter>(pawn);
	TArray<APuzzleKeyActor*> ToRemoveActors;
	if (player->HeldKeys.Num() > 0)
	{
		for(APuzzleKeyActor* Soul : player->HeldKeys)
		{
			if (Soul->TypeOfSoul == TypeOfSoul)
			{
				Soul->Execute_OnTurnIn(Soul,Cast<AActor>(this));
				TotalSoulsTurnedIn++;
				ToRemoveActors.Add(Soul);			
			}
		}
		for (APuzzleKeyActor* Soul : ToRemoveActors)
		{
			player->HeldKeys.Remove(Soul);
		}
		ToRemoveActors.Empty();
	}
	if (TotalSoulsTurnedIn == TotalSoulsNeeded)
	{
		//TODO: Open the gates
		//TODO: Light up the Lantern
		//TODO: Make liftable object unliftable
		Execute_OnSolved(this);
	}
	
}

void APuzzleActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ATeam09_DarkLightCharacter* player = Cast<ATeam09_DarkLightCharacter>(OtherActor);
	if (player != NULL)
	{
		TryToSolveWithKeys(player);
	}

}



