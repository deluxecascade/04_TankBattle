// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// ENUM for firing states
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;

// Hold's barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UTankAimingComponent();


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

private:
	
	
	void MoveBarrelTowards(FVector AimDirection);

	
};
