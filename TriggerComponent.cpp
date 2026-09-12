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
	if (MoverActor != nullptr){
		
		// FindComponentByClass is the function that will find the Mover component inside the MoverActor, 
		// and return the ptr of the Mover component, and after we find the ptr we can 
		// use it to call the function inside the Mover component, like ShouldMove, MoveOffset, etc.
		Mover = MoverActor->FindComponentByClass<UMover>();
		if (Mover != nullptr){
			UE_LOG(LogTemp, Warning, TEXT("Mover ptr is valid"));
			Mover->ShouldMove = true;
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Mover ptr is not valid"));
		}
	}
	
	// if not find it will return nullptr
	else{
		UE_LOG(LogTemp, Warning, TEXT("MoverActor is nullptr"));
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Trigger Component BeginPlay"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//UE_LOG(LogTemp, Warning, TEXT("Trigger Component TickComponent"));
}
