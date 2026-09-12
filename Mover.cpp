// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// Get the Actor of this component, in this case is this door
	//AActor* MyOwner = GetOwner();
	
	StartLocation = GetOwner()->GetActorLocation();
	
	//UE_LOG(Log Temp, Warning, TEXT("Actor owner is %s"), *GetOwner()->GetActorNameOrLabel());
	
	//UE_LOG(LogTemp, Warning, TEXT("StartLocation is %s"), *StartLocation.ToCompactString());
	
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (ShouldMove == true)
	{
		TargetLocation = StartLocation + MoveOffset;
	}
	else
	{
		TargetLocation = StartLocation;
	}
	
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	
	// Return bool weather the current location is equal to the target location
	ReachTarget = CurrentLocation.Equals(TargetLocation);
	
	// Once we reach the target location, we stop moving
	if (ReachTarget == false)
	{
		float Speed = MoveOffset.Length() / MoveTime;
		// VInterpConstantTo is a “move toward a target at a constant rate” helper.
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		
		// Update the location of the actor that owns this component in every frame 
		GetOwner()->SetActorLocation(NewLocation);
	}
}

