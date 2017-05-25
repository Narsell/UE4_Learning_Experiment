// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCOURSE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
		float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	AActor* Player = GetOwner();

	//Raycast and grab what's in reach
	void Grab(); 
	//Called when grab is released
	void Release();
	//Look for the attached physics handle component.
	void FindPhysicsComponent();
	//Look for the attached (in play time) input component.
	void SetupInputComponent();
	//Returns FHitResult of the first physics body in range
	FHitResult const GetPhysicsBodyInReach();
	
};
