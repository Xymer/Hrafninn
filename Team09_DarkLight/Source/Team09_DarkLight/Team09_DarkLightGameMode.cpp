// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team09_DarkLightGameMode.h"
#include "Team09_DarkLightCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeam09_DarkLightGameMode::ATeam09_DarkLightGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
