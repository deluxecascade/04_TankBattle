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
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ Construct"), *TankName)


}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ BeginPlay"), *TankName)
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}


//// Called every frame
//void ATank::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	// AimTowardsCrosshair();
//}



void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool IsReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTime);
	if (IsReloaded) 
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
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