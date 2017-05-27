// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCOURSE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenCloseDoor(float Yaw);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float MassOnPressurePlate();

	UPROPERTY(EditAnywhere)
		float OpenAngle = -90.f;
	UPROPERTY(EditAnywhere)
		float CloseAngle = 0.f;
	UPROPERTY(EditAnywhere)
		float CloseDoorDelay = 0.7f;

	//Giving this a value to avoid errors if the players wont step on the trigger.
	float openDoorTime = 0.f; 

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	AActor* Door = GetOwner();

	
};
