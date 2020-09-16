// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabbing_Component.h"
#include <DrawDebugHelpers.h>
#include "Team09_DarkLightCharacter.h"
#include <Components/ActorComponent.h>
#include <Engine/Engine.h>
#include <Math/Rotator.h>
#include <Team09_DarkLight\RealmObjectActor.h>
#include "GrabbableInterface.h"
#include <Components/PrimitiveComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Math/UnrealMathUtility.h>






// Sets default values for this component's properties
UGrabbing_Component::UGrabbing_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabbing_Component::BeginPlay()
{
	Super::BeginPlay();
	CheckForPhysicsHandler();
	InputHandling();
}

void UGrabbing_Component::InputHandling()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabbing_Component::PushPull);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabbing_Component::StopPushPull);
	}
}

void UGrabbing_Component::CheckForPhysicsHandler()
{

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component on %s"), *GetOwner()->GetName());
	}
}

void UGrabbing_Component::PushPull()
{
	GetObjectInReach();
	if (Player->HeldItem)
	{
		Player->FindComponentByClass<UCharacterMovementComponent>()->bOrientRotationToMovement = false;
		Player->FindComponentByClass<UCharacterMovementComponent>()->bUseControllerDesiredRotation = false;
		Player->FindComponentByClass<UCharacterMovementComponent>()->MaxAcceleration = HeldItemAccelerationAdjust;
		Execute_OnPushing(this);
	}
}

void UGrabbing_Component::StopPushPull()
{
	PhysicsHandle->ReleaseComponent();
	if (Player->HeldItem)
	{
		Player->FindComponentByClass<UCharacterMovementComponent>()->bOrientRotationToMovement = true;
		Player->FindComponentByClass<UCharacterMovementComponent>()->bUseControllerDesiredRotation = true;
		Player->FindComponentByClass<UCharacterMovementComponent>()->MaxAcceleration = 1000.f;
		Player->HeldItem = nullptr;
		GrabbedItemComponent = nullptr;
		Execute_OnReleaseObject(this);
	}
}

void UGrabbing_Component::SetOwner(ATeam09_DarkLightCharacter* Owner)
{
	if (!Player)
	{
		Player = Owner;
	}
}

FHitResult UGrabbing_Component::GetObjectInReach()
{
	CurrentOwner = GetOwner();

	if (CurrentOwner)
	{
		FHitResult ItemHit;
		StartLineTrace;
		ExtensionFromStartLineTrace = GetOwner()->GetActorForwardVector();
		RotatelineTrace = GetOwner()->GetActorRotation();

		CurrentOwner->GetActorEyesViewPoint(StartLineTrace, RotatelineTrace);

		EndofLineTrace = StartLineTrace + ExtensionFromStartLineTrace * Reach;

		FCollisionQueryParams TraceQueryParams;
		TraceQueryParams.AddIgnoredActor(CurrentOwner);
		TraceQueryParams.bTraceComplex = true;

		if (GetWorld()->LineTraceSingleByChannel(ItemHit, StartLineTrace, EndofLineTrace, ECC_PhysicsBody, TraceQueryParams))
		{
			AActor* Actorhit = nullptr;
			ARealmObjectActor* Object = Cast<ARealmObjectActor>(ItemHit.GetActor());
			if (Object)
			{
				if (Object->bIsGrabbable)
				{
					Actorhit = ItemHit.GetActor();
				}
			}

				if (Actorhit)
				{
					GrabbedItemComponent = ItemHit.GetComponent();
					FRotator GrabbedItemRotation = CurrentOwner->GetActorForwardVector().Rotation();
					FVector LiftLocation = FVector(EndofLineTrace.X + Player->GetActorForwardVector().X * 10.f, EndofLineTrace.Y + Player->GetActorForwardVector().Y * 10.f, EndofLineTrace.Z * 1.0375f);
					distance = FVector::Distance(Player->GetActorLocation(), ItemHit.ImpactPoint);
					PhysicsHandle->GrabComponentAtLocationWithRotation(GrabbedItemComponent, NAME_None, ItemHit.ImpactPoint + Player->GetActorForwardVector(), GrabbedItemRotation);
					Object->SetActorLocationAndRotation(PhysicsHandle->GrabbedComponent->GetComponentLocation(), GrabbedItemRotation);
					Player->HeldItem = Actorhit;
				}		
		}
	}
	return FHitResult();
}

// Called every frame
void UGrabbing_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateGrabbedItemLocation();
}

void UGrabbing_Component::UpdateGrabbedItemLocation()
{
	if (!Player->HeldItem)
	{
		return;
	}
	if (FVector::Distance(Player->GetActorLocation(),Player->HeldItem->GetActorLocation()) > DistanceToReleaseObject)
	{
		StopPushPull();
	}

	CurrentOwner = GetOwner();
	CurrentOwner->GetActorEyesViewPoint(StartLineTrace, RotatelineTrace);
	EndofLineTrace = StartLineTrace + ExtensionFromStartLineTrace * Reach;

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocationAndRotation(Player->GetActorLocation() + Player->GetActorForwardVector() * (distance + distanceOffset), CurrentOwner->GetActorForwardVector().Rotation());
		FTransform GrabbedTransform = PhysicsHandle->GrabbedComponent->GetComponentTransform();
		GrabbedItemComponent->GetOwner()->SetActorLocation(GrabbedItemComponent->GetComponentLocation());
	}
}

