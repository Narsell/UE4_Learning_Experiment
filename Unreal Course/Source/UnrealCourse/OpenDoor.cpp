// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCourse.h"
#include "OpenDoor.h"
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

void UOpenDoor::OpenCloseDoor(float Yaw)
{
	Door->SetActorRotation(FRotator(0.f, Yaw, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MassOnPressurePlate() > 95.f) //If ActorThatOpens is in the Preassure Plate boundaries, open the door.
	{
		OpenCloseDoor(openAngle);
		openDoorTime = GetWorld()->GetRealTimeSeconds();
	}
	else
		if (GetWorld()->GetRealTimeSeconds() - openDoorTime > closeDoorDelay)
			OpenCloseDoor(closeAngle);
	
}

float UOpenDoor::MassOnPressurePlate()
{
	float TotalMass = 0.f;
	//Find all the overlaping actors
	TArray<AActor*> OverlappingActors; 
	PressurePlate->GetOverlappingActors(OUT OverlappingActors); //Out parameters.

	//Add their masses.
	for (const auto* Actor : OverlappingActors) //New C++11 range based for loops.
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass(); //IMPORTANT, the mass on an actor is an UPrimitiveComponent, so we'll get access to it through there
		UE_LOG(LogTemp, Warning, TEXT("%s is on pressure plate"), *Actor->GetName())
	}

	return TotalMass;
}