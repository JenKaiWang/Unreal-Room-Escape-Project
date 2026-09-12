// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h" // now we have the access to the Mover class, so we can use it in this TriggerComponent class

// if we ever need to include any new header files, we need to include them above here
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONESCAPE_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Make the connection with this Trigger Component to the actor own the Mover Component which is the Room1DoorShape
	UPROPERTY(EditAnywhere)
	AActor* MoverActor;
	
	// Store the ptr of the Actor own the Mover Component so we can use it inside the Trigger Component class
	UMover* Mover;
};
