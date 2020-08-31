// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulActor.h"
#include "Team09_DarkLightCharacter.h"



// Sets default values
ASoulActor::ASoulActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASoulActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ASoulActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoulActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASoulActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult & SweepHitResult)
{
	ATeam09_DarkLightCharacter* player = Cast<ATeam09_DarkLightCharacter>(OtherActor);
	if (player != nullptr)
	{
		player->PickUpKey(this);
		bIsPickedUp = true;
		Execute_OnPickedUp(this,Cast<APawn>(player));
	}
}


