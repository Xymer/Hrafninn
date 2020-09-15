// Fill out your copyright notice in the Description page of Project Settings.


#include "ALevelList.h"
#include "Engine/ObjectLibrary.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UALevelList::UALevelList()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UALevelList::LoadLevel()
{
	FString MapString;
	FName MapName;
	switch (EMapList)
	{
	case EMapList::Level1:
		MapString = FString(TEXT("L_Tutorial_Lvl1c"));
		break;
	case EMapList::Level2:
		MapString = FString(TEXT("L_GroundFloor_Lvl2c"));
		break;
	case EMapList::Level3:
		MapString = FString(TEXT("L_Attic_Level3c"));
		break;
	case EMapList::Level4:
		MapString = FString(TEXT("L_Credits"));
		break;
	case EMapList::Level5:
		MapString = FString(TEXT("L_StartLevel"));
		break;
	}

	if (MapString.IsEmpty())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("monkey"));
		LevelNullCheck(MapString);
		return;
	}
	else
	{
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("flip"));
		MapName = FName(MapString);
		UGameplayStatics::OpenLevel(this, MapName, true);
	}
}

void UALevelList::LevelNullCheck(FString  MapString)
{
	FName MapName = FName(MapString);
	FString currentLevel = GetWorld()->GetName();
	if (currentLevel == "L_Tutorial_Lvl1c")
	{
		MapName = FName(TEXT("L_GroundFloor_Lvl2c"));
	}
	else if (currentLevel == "L_GroundFloor_Lvl2c")
	{
		MapName = FName(TEXT("L_Attic_Level3c"));
	}
	else if (currentLevel == "L_Attic_Level3c")
	{
		MapName = FName(TEXT("L_Credits"));
	}
	UGameplayStatics::OpenLevel(this, MapName, true);
}


