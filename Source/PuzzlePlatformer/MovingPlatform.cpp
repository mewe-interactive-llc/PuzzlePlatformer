// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
AMovingPlatform::AMovingPlatform()
{
	SetMobility(EComponentMobility::Movable);
	PrimaryActorTick.bCanEverTick = true;
	
	MaxSpeed = 5.f;
}



void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true); // this replicates to the client
		SetReplicateMovement(true); //this replicates movement to the client
	}
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		Location += FVector(MaxSpeed * DeltaTime, 0.f, 0.f);
		SetActorLocation(Location);
	}

	
}
