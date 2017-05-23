// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCourse.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ViewPointLocation;
	FRotator ViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPointLocation, ViewPointRotator); // I pass two empty variables to this function and it will modify them on the inside with the PlayerViewPoint values.

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s,  Rotation: %s"), *ViewPointLocation.ToString(), *ViewPointRotator.ToString() )

	FVector VectorEnd = ViewPointLocation + ViewPointRotator.Vector()*Reach; //Basic vector addition.

	DrawDebugLine(GetWorld(), ViewPointLocation, VectorEnd, FColor(0, 255, 0), false, 0.f, 0.f, 10.f);

}

