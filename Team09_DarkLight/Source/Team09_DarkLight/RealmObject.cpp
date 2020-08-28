// Fill out your copyright notice in the Description page of Project Settings.


#include "RealmObject.h"
#include "Kismet/GameplayStatics.h"
#include "RealmObjectActor.h"
#include "PuzzleKeyActor.h"
#include "PuzzleActor.h"
#include <Components/StaticMeshComponent.h>


// Add default functionality here for any IRealmObject functions that are not pure virtual.


void IRealmObject::OnSwapRealm_Implementation(RealmType CurrentRealm)
{
	SwapVisibility(CurrentRealm);
}

void IRealmObject::SwapVisibility(RealmType CurrentRealm)
{
	ARealmObjectActor* RealmActor = Cast<ARealmObjectActor>(this);
	APuzzleKeyActor* PuzzleKeyActor = Cast<APuzzleKeyActor>(this);
	APuzzleActor* PuzzleActor = Cast<APuzzleActor>(this);
	if (RealmActor != nullptr)
	{
		UStaticMeshComponent* mesh = RealmActor->FindComponentByClass<UStaticMeshComponent>();
		mesh->SetVisibility(RealmActor->VisibleRealm == CurrentRealm);
		if (RealmActor->VisibleRealm == CurrentRealm)
		{
			mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	else if (PuzzleKeyActor != nullptr)
	{
		UStaticMeshComponent* mesh = PuzzleKeyActor->FindComponentByClass<UStaticMeshComponent>();
		mesh->SetVisibility(PuzzleKeyActor->VisibleRealm == CurrentRealm);
		if (PuzzleKeyActor->VisibleRealm == CurrentRealm)
		{
			mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	else if (PuzzleActor != nullptr)
	{
		UStaticMeshComponent* mesh = PuzzleActor->FindComponentByClass<UStaticMeshComponent>();
		mesh->SetVisibility(PuzzleActor->VisibleRealm == CurrentRealm);
		if (PuzzleActor->VisibleRealm == CurrentRealm)
		{
			mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

