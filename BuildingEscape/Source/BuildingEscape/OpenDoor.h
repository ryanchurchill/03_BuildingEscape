// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OpenDoor.generated.h"

class UActorComponent;
class ATriggerVolume;
class AButtonActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets default values for this component's properties
	UOpenDoor();

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AButtonActor* Button = nullptr;

	UFUNCTION()
	void OnPressurePlateChange(AActor * OverlappedActor, AActor * OtherActor);

	float GetTotalMassOfActorsOnPlate();

	UPROPERTY(EditAnywhere)
	float TriggerMass = 1.f;
};
