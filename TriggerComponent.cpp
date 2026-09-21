// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Trigger Component Constructor"));
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// we need to make sure the MoverActor is not nullptr before we try to find the Mover component
	// the null ptr will make the game crash
	if (MoverActor) // MoverActor != nullptr
	{
		
		// FindComponentByClass is the function that will find the Mover component inside the MoverActor, 
		// and return the ptr of the Mover component, and after we find the ptr we can 
		// use it to call the function inside the Mover component, like ShouldMove, MoveOffset, etc.
		Mover = MoverActor->FindComponentByClass<UMover>();
		if (Mover) //Mover != nullptr
		{
			UE_LOG(LogTemp, Warning, TEXT("Mover ptr is valid"));
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Mover ptr is not valid"));
		}
	}
	// if not find it will return nullptr
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MoverActor is nullptr"));
	}
	
	// Not all the TriggerComponent is a pressure plate, 
	// so we need to check if it is a pressure plate before we bind the overlap event
	if (IsPressurePlate)
	{
		// this part is how we bind the OnOverlapBegin and OnOverlapEnd functions
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Trigger Component BeginPlay"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// This is the reusable function that will be called when the player character overlap with the item in the level
void UTriggerComponent::Trigger(bool NewTriggerValue)
{
	IsTriggered = NewTriggerValue;
	
	if (Mover)
	{
		Mover->SetShouldMove(IsTriggered);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s doesn't have a mover to trigger"), *GetOwner()->GetActorNameOrLabel());
	}
	
}

// This function will be called when the player character overlap with the trigger box, 
void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ActorHasTag will return boolean value
	// Check if the OtherActor has the tag "PressurePlateActivator", if it does, we will set the ShouldMove to true
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		//Track how many activator on top of the pressure plate
		ActivatorCount++;
		
		if (!IsTriggered)
		{
			Trigger(true);
		}
	}
}

// This function will be called when the player character stops overlapping with the trigger box, 
void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		
		ActivatorCount--;
		
		if (IsTriggered && ActivatorCount == 0)
		{
			Trigger(false);
		}
	}
}
