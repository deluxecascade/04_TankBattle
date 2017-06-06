// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBattle.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"



void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool IsReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTime);

	bool OutOfAmmo = (Ammo <= 0);

	if (OutOfAmmo)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if (!IsReloaded)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, .01);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace)
		)
	
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("At %f AimDirection: %s"), Time,*AimDirection.ToString())
		MoveBarrelTowards(AimDirection);
		
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No AimAt Solution"), Time)
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector InAimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	//Work-out difference between current barrel position
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = InAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Keeps the turret rotator below 180 so it always uses the shortest rotation possible
	if (DeltaRotator.Yaw > 180)
	{
		DeltaRotator.Yaw = -(360 - DeltaRotator.Yaw);
	}

	if (DeltaRotator.Yaw < -180)
	{
		DeltaRotator.Yaw = (360 + DeltaRotator.Yaw);
	}



	/* Tells barrel to elevate up or down depending on whether the 
	 AimDirection is asking for something higher or lower than the current barrel position*/
	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);
}
void UTankAimingComponent::Fire()
{
	if ((FiringState != EFiringState::Reloading) && (FiringState != EFiringState::OutOfAmmo))
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		Ammo--;

		//Not sure why the variables cause the SpawnActor function to not compile
		//auto ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
		//auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
		////Spawn projectile on the end of the barrel
		//
		//GetWorld->SpawnActor<AProjectile>(
		//	ProjectileBlueprint,
		//	ProjectileLocation,
		//	ProjectileRotation
		//	);
	}
}

int UTankAimingComponent::GetAmmo() 
{
	return Ammo;
}