// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"
#include "Math/Quat.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Could not find PressurePlate for object %s"), *(GetOwner()->GetName()));
	}
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) // TODO: make into param
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}

	if (Button) {
		UStaticMeshComponent* smc = Button->GetStaticMeshComponent();
		FString hidden = FString::FromInt(smc->bHiddenInGame);
		UE_LOG(LogTemp, Warning, TEXT("Hidden: %s"), *hidden);
		if (hidden == "1")
		{
			OnOpen.Broadcast();
		}
	}
	
}


float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) {		
		return 0.f;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// Iterate through them, adding masses
	for (const AActor* Actor : OverlappingActors) {		
		float Mass = Actor->GetRootPrimitiveComponent()->GetMass();
		TotalMass += Mass;
		//UE_LOG(LogTemp, Warning, TEXT("Actor Found: %s with mass: %f"), *Actor->GetName(), Mass);
	}

	return TotalMass;
}