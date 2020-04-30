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

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);

	
	
	if (HasAuthority())
	{
		FVector CurrentLocation = GetActorLocation();
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (CurrentLocation - GlobalStartLocation).Size();

		if (JourneyTravelled > JourneyLength)
		{
			Swap(GlobalTargetLocation, GlobalStartLocation);
		}


		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		CurrentLocation += MaxSpeed * DeltaTime * Direction;
		SetActorLocation(CurrentLocation);

		
	}

	
}
