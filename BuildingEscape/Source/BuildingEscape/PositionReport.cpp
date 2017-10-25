// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"
#include "Math/Vector.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	FString ObjectName = Owner->GetName();
	FVector Position = Owner->GetTransform().GetTranslation();
	//FText XPos = FText::AsNumber(Position.X);
	//FText YPos = FText::AsNumber(Position.Y);
	//FText ZPos = FText::AsNumber(Position.Z);
	FString PositionsStr = Position.ToString();
	//FString ObjectPos = FText::Format(TEXT("X=%s, Y=%s, Z=%s"), XPos, YPos, ZPos);
	FString ObjectPosStr2 = FString::Printf(TEXT("X=%3.3f Y=%3.3f Z=%3.3f"), Position.X, Position.Y, Position.Z);
	//FString ObjectPos = FText::Format(TEXT("hello"));

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *PositionsStr);
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

