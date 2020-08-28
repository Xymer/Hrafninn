// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RealmType.h"
#include "RealmObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URealmObject : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class TEAM09_DARKLIGHT_API IRealmObject
{
	GENERATED_BODY()
public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnSwapRealm(RealmType CurrentRealm);
	void OnSwapRealm_Implementation(RealmType CurrentRealm);

	virtual void SwapVisibility(RealmType CurrentRealm);

};
