// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//No need to protect points as added at constrution
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

//// Called every frame
//void ATank::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	// AimTowardsCrosshair();
//}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE!!"))

	if (!Barrel) { return; }

	GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		 );
}

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