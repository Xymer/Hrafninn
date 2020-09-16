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
		PointLightComponent->SetIntensity(FMath::FInterpTo(PointLightComponent->Intensity, CurrentIntensity, DeltaTime, IntensityLerpSpeed));
	}
}

void ALanternActor::SetKeysToSolve()
{

}

void ALanternActor::TryToSolveWithKeys(APawn* pawn, RealmType CurrentRealm)
{
	ATeam09_DarkLightCharacter* player = Cast<ATeam09_DarkLightCharacter>(pawn);
	TArray<ASoulActor*> ToRemoveActors;
	if (CurrentRealm == VisibleRealm)
	{
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
			if (GatesToOpen.Num() > 0)
			{
				for (AGateActor* item : GatesToOpen)
				{
					item->Execute_OnOpen(item);
				}

			}
			Execute_OnSolved(this);
		}
	}
}


void ALanternActor::IncreaseIntensity(float Value)
{
	if (TotalSoulsNeeded >= TotalSoulsTurnedIn)
	{
		CurrentIntensity += Value;
	}
}



