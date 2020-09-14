// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ALevelList.generated.h"

UENUM(BlueprintType)
enum class EMapList : uint8
{
	Level1  UMETA(DisplayName = "L_Tutorial_Lvl1"),
	Level2  UMETA(DisplayName = "L_GroundFloor_Lvl2"),
	Level3  UMETA(DisplayName = "L_Attic_Level3"),
	Level4  UMETA(DisplayName = "L_Credits"),
	Level5  UMETA(DisplayName = "L_StartScreen"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM09_DARKLIGHT_API UALevelList : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UALevelList();

	UPROPERTY(EditAnywhere, Category = "Level Transition")
		TEnumAsByte<EMapList> EMapList;

public:	

	UFUNCTION(BlueprintCallable)
		void LoadLevel();

		void LevelNullCheck(FString MapString);

};
