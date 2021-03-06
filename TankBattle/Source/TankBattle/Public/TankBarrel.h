// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision")
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 max doward speed and + 1 is max up movement
	void Elevate(float RelativeSpeed);
	
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevation = 45;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevation = 0;
	
};
