// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;


UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();



protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//// Called every frame
	//virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 40000; //TODO find sensible default


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3;

	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;
	
};
