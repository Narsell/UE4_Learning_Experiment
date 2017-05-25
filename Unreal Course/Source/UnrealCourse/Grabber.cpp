// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCourse.h"
#include "Grabber.h"
#define OUT //Just to know when a param its out in the func call.


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

	///Look for the attached physics handle component.
	PhysicsHandle = Player->FindComponentByClass<UPhysicsHandleComponent>(); // We find the component doing a top-down search and looking the component of type UPhysicsHandleComponent.
	if(PhysicsHandle)
	{ 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle Component found in Actor %s, please add one"), *(Player->GetName()) )
	}

	///Look for the attached (in play time) input component.

	InputComponent = Player->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component found in Actor %s"), *(Player->GetName()))
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{ 
		UE_LOG(LogTemp, Error, TEXT("No Input Component found in Actor %s"), *(Player->GetName()))
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///Getting the players viewpoint.
	FVector ViewPointLocation;
	FRotator ViewPointRotator;


	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPointLocation, ViewPointRotator);// I pass two empty variables to this function and it will modify them on the inside with the PlayerViewPoint values.


	///Calculating the Vector that points in the direction of the players "eye" and drawing a GREEN trace into the world to visualise.
	FVector VectorEnd = ViewPointLocation + ViewPointRotator.Vector()*Reach; //Basic vector addition.
	DrawDebugLine(GetWorld(), ViewPointLocation, VectorEnd, FColor(0, 255, 0), false, 0.f, 0.f, 10.f);

	///Now getting the ray cast out.
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectTypes(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, Player);

	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewPointLocation, VectorEnd, ObjectTypes, TraceParameters);

	///Logging to the console what we hit.
	AActor* ActorHit = Hit.GetActor();

	if(ActorHit) //To avoid doing this when a null pointer gets returned because the player is not looking at an physicsBody Actor.
		UE_LOG(LogTemp, Warning, TEXT("Ouch, you just hit a %s, have a little respect bud"), *(ActorHit->GetName()) )

	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))
}

