// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCourse.h"
#include "OpenDoor.h"


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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); //We look from top to bottom for the "mind" of the player, then we look from botton to top to the AActor (Pawn in this case) that is being controlled by the "mind"
	
}

void UOpenDoor::OpenCloseDoor(float Yaw)
{
	Door->SetActorRotation(FRotator(0.f, Yaw, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) //If ActorThatOpens is in the Preassure Plate boundaries, open the door.
	{
		OpenCloseDoor(openAngle);
		openDoorTime = GetWorld()->GetRealTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetRealTimeSeconds() - openDoorTime > closeDoorDelay)
			OpenCloseDoor(closeAngle);
	}
	
	
	
}

