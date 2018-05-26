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
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > 50.f) // TODO: make into param
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() > LastDoorOpenTime + DoorCloseDelaySecs) {
			CloseDoor();
		}
	}
}


void UOpenDoor::OpenDoor()
{
	// Find the owning actor
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.f, -90.f, 0.f);

	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	// Find the owning actor
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.f, 180.f, 0.f);

	Owner->SetActorRotation(NewRotation);
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// Iterate through them, adding masses
	for (const AActor* Actor : OverlappingActors) {		
		float Mass = Actor->GetRootPrimitiveComponent()->GetMass();
		TotalMass += Mass;
		UE_LOG(LogTemp, Warning, TEXT("Actor Found: %s with mass: %f"), *Actor->GetName(), Mass);
	}

	return TotalMass;
}