// Fill out your copyright notice in the Description page of Project Settings.


#include "GateActor.h"

// Sets default values
AGateActor::AGateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

