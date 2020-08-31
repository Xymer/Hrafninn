// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabbing_Component.h"
#include <DrawDebugHelpers.h>
#include "Team09_DarkLightCharacter.h"
#include <Components/ActorComponent.h>
#include <Engine/Engine.h>
#include <Math/Rotator.h>






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

	if (PhysicsHandle)
	{
		//Physics Handle Component found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component on %s"), *GetOwner()->GetName());
	}
}

void UGrabbing_Component::PushPull()
{
	GetObjectInReach();
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Green, FString("PushPull pressed"), true);
}

void UGrabbing_Component::StopPushPull()
{
	/*PhysicsHandle->ReleaseComponent();*/
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Green, FString("PushPull released"), true);
}

FHitResult UGrabbing_Component::GetObjectInReach()
{
	AActor* CurrentOwner = GetOwner();

	if (CurrentOwner)
	{
		FHitResult ItemHit;
		FVector StartLineTrace;
		FVector RotatingLineTrace = GetOwner()->GetActorForwardVector();
		FRotator RotatelineTrace = GetOwner()->GetActorRotation();

		CurrentOwner->GetActorEyesViewPoint(StartLineTrace, RotatelineTrace);

		FVector EndofLineTrace = StartLineTrace + GetOwner()->GetActorForwardVector() * Reach;

		FCollisionQueryParams TraceQueryParams;
		TraceQueryParams.AddIgnoredActor(CurrentOwner);
		TraceQueryParams.bTraceComplex = true;

		if (GetWorld()->LineTraceSingleByChannel(ItemHit, StartLineTrace, EndofLineTrace, ECC_PhysicsBody, TraceQueryParams))
		{

			AActor* Actorhit = ItemHit.GetActor();
			UPrimitiveComponent* GrabbedItemComponent = ItemHit.GetComponent();
			FRotator GrabbedItemRotation = GrabbedItemComponent->GetComponentRotation();

			if (Actorhit)
			{
				PhysicsHandle->GrabComponentAtLocationWithRotation(GrabbedItemComponent, NAME_None, EndofLineTrace, RotatelineTrace);
				GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString(Actorhit->GetName()), true);
				UE_LOG(LogTemp, Warning, TEXT("Trace has hit: %s"), *(Actorhit->GetName()));
			}

		}

		DrawDebugLine(GetWorld(), StartLineTrace, EndofLineTrace, FColor::Red, false, 05.f);
	}
	return FHitResult();
}

// Called every frame
void UGrabbing_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	AActor* CurrentOwner = GetOwner();
	FVector StartLineTrace;
	FVector RotatingLineTrace = GetOwner()->GetActorForwardVector();
	FRotator RotatelineTrace = CurrentOwner->GetActorRotation();

	CurrentOwner->GetActorEyesViewPoint(StartLineTrace, RotatelineTrace);

	FVector EndofLineTrace = StartLineTrace + GetOwner()->GetActorForwardVector() * Reach;
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocationAndRotation(EndofLineTrace, RotatelineTrace);

	}
}

