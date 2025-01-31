// Fill out your copyright notice in the Description page of Project Settings.


#include "RealmObject.h"
#include "Kismet/GameplayStatics.h"
#include "RealmObjectActor.h"
#include "SoulActor.h"
#include "LanternActor.h"
#include <Components/StaticMeshComponent.h>


// Add default functionality here for any IRealmObject functions that are not pure virtual.


void IRealmObject::OnSwapRealm_Implementation(RealmType CurrentRealm)
{
	SwapVisibility(CurrentRealm);
}

void IRealmObject::SwapVisibility(RealmType CurrentRealm)
{
	ARealmObjectActor* RealmActor = Cast<ARealmObjectActor>(this);
	ASoulActor* PuzzleKeyActor = Cast<ASoulActor>(this);
	ALanternActor* PuzzleActor = Cast<ALanternActor>(this);
	if (RealmActor != nullptr)
	{
		if (!RealmActor->bIsAffectedByRealm)
		{
			return;
		}
		
		UStaticMeshComponent* mesh = RealmActor->FindComponentByClass<UStaticMeshComponent>();
		USkeletalMeshComponent* skelMesh = RealmActor->FindComponentByClass<USkeletalMeshComponent>();
		if (skelMesh)
		{
			skelMesh->SetVisibility(RealmActor->VisibleRealm == CurrentRealm);
		}
		if (mesh)
		{
			mesh->SetVisibility(RealmActor->VisibleRealm == CurrentRealm);

		}
		if (RealmActor->VisibleRealm == CurrentRealm)
		{
			if (skelMesh)
			{
				skelMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			}
			mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			if (skelMesh)
			{
				skelMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
			mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	else if (PuzzleKeyActor != nullptr)
	{
		if (PuzzleKeyActor->bIsPickedUp || !PuzzleKeyActor->bIsAffectedByRealm)
		{
			return;
		}
		UStaticMeshComponent* mesh = PuzzleKeyActor->FindComponentByClass<UStaticMeshComponent>();
		UBoxComponent* box = PuzzleKeyActor->FindComponentByClass<UBoxComponent>();
		mesh->SetVisibility(PuzzleKeyActor->VisibleRealm == CurrentRealm);
		if (PuzzleKeyActor->VisibleRealm == CurrentRealm)
		{
			mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	else if (PuzzleActor != nullptr)
	{
		if (!PuzzleActor->bIsAffectedByRealm)
		{
			return;
		}
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

