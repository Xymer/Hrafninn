// Fill out your copyright notice in the Description page of Project Settings.


#include "LanternActor.h"
#include "Team09_DarkLightCharacter.h"
#include <Math/Color.h>
#include <Containers/UnrealString.h>

// Sets default values
ALanternActor::ALanternActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALanternActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ALanternActor::BeginPlay()
{
	Super::BeginPlay();
	TArray<UPointLightComponent*> children;
	GetComponents(children);

	for (UPointLightComponent* child : children)
	{
		if (child != nullptr)
		{
			PointLightComponent = child;
		}
	}
	IncreaseIntensityBy = PointLightComponent->Intensity / TotalSoulsNeeded;
	PointLightComponent->SetIntensity(0);
}

// Called every frame
void ALanternActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentIntensity >= PointLightComponent->Intensity)
	{
		PointLightComponent->SetIntensity(FMath::FInterpTo(PointLightComponent->Intensity,CurrentIntensity,DeltaTime,IntensityLerpSpeed));		
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString::SanitizeFloat(PointLightComponent->Intensity), true);
	}
}

void ALanternActor::SetKeysToSolve()
{

}

void ALanternActor::TryToSolveWithKeys(APawn* pawn)
{
	ATeam09_DarkLightCharacter* player = Cast<ATeam09_DarkLightCharacter>(pawn);
	TArray<ASoulActor*> ToRemoveActors;
	if (player->HeldSouls.Num() > 0)
	{
		for (ASoulActor* Soul : player->HeldSouls)
		{
			if (Soul->TypeOfSoul == TypeOfSoul)
			{
				Soul->Execute_OnTurnIn(Soul, Cast<AActor>(this));
				TotalSoulsTurnedIn++;
				IncreaseIntensity(IncreaseIntensityBy);
				ToRemoveActors.Add(Soul);
			}
		}
		for (ASoulActor* Soul : ToRemoveActors)
		{
			player->HeldSouls.Remove(Soul);
		}
		ToRemoveActors.Empty();
	}
	if (TotalSoulsTurnedIn == TotalSoulsNeeded)
	{
		if (GateToOpen)
		{
			GateToOpen->Execute_OnOpen(GateToOpen);
		}		
		//TODO: Make liftable object unliftable
		Execute_OnSolved(this);
	}
}

void ALanternActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ATeam09_DarkLightCharacter* player = Cast<ATeam09_DarkLightCharacter>(OtherActor);
	if (player != NULL)
	{
		TryToSolveWithKeys(player);
	}
}

void ALanternActor::IncreaseIntensity(float Value)
{
	if (TotalSoulsNeeded >= TotalSoulsTurnedIn)
	{
		CurrentIntensity += Value;		
	}
}



