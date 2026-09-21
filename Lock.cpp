// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock.h"

// Sets default values
ALock::ALock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// create component inside C++ USE CreateDefaultSubobject<>() function, and then attach it to the root component
	// we can also do this in the blueprint, but we will do it in the C++ code to make it more reusable
	// and can be more flexible design
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);
	
	TriggerComp = CreateDefaultSubobject<UTriggerComponent>(TEXT("Trigger Comp"));
	TriggerComp->SetupAttachment(RootComp);
	
	KeyItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Item Mesh"));
	KeyItemMesh->SetupAttachment(RootComp);
	
	Tags.Add("Lock");

}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	SetIsKeyPlaced(true);
}

// Called every frame
void ALock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UE_LOG(LogTemp, Warning, TEXT("Current time: %f"), GetWorld()->TimeSeconds);
}

void ALock::SetIsKeyPlaced(bool NewIsKeyPlaced)
{
	IsKeyPlaced = NewIsKeyPlaced;
	
	// If the key is placed, we will trigger the door to open, and make the key mesh visible
	// If the key is not placed, we will trigger the door to close, and make the key mesh invisible
	TriggerComp->Trigger(NewIsKeyPlaced);
	KeyItemMesh->SetVisibility(NewIsKeyPlaced);
}

bool ALock::GetIsKeyPlaced()
{
	return IsKeyPlaced;
}

