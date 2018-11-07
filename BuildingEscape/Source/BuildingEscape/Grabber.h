// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Grabber.generated.h"

class AButtonActor;
class UInputComponent;
class UPhysicsHandleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// How far ahead of the player we can reach in cm
	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach
	// Bound to "Grab" Input via SetupInputComponent function
	void Grab();
	void PushDoorButton(AButtonActor* ComponentToGrab);
	void Release();

	void FindPhysicsHandleComponent();

	void SetupInputComponent();

	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;

	FVector GetReachLineStart() const;
	FVector GetReachLineEnd() const;
};
