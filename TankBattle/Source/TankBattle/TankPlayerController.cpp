// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::DelegateDeathMethod);
	}


}

void ATankPlayerController::DelegateDeathMethod()
{
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}
 


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; //Out parameter
	bool bGetHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGetHitLocation)// Has "side-effect; is going to line trace
	{
		// Tell controlled tank to aim at this point
		AimingComponent->AimAt(HitLocation);
		
	
	}
	
	
}

// Get world location of line trace through crosshairs, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D((ViewportSizeX * CrossHairXLocation), (ViewportSizeY*CrossHairYLocation));
	
	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to a max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	
	}

	// Line-trace along that look direction, and see what we hit (up to max range)
	return false;
}


// "De-project" the screen position of the crosshair to a world direction passed out as LookDirection reference
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector WorldCameraLocation;
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldCameraLocation, LookDirection));
	
		
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	
	//UWorld* World = GetWorld();
	FHitResult OutHit;
	FVector HitStart = PlayerCameraManager->GetCameraLocation();
	FVector HitEnd = HitStart + LookDirection * LineTraceRange;
	FCollisionResponseParams ResponseParams;
	
	if (GetWorld()->LineTraceSingleByChannel
	(
		OutHit,
		HitStart,
		HitEnd,
		ECollisionChannel::ECC_Camera //was ECC_Visibility
	))
	{
		HitLocation = OutHit.Location;
		return true;
	}
	else 
	{ 
		HitLocation = FVector(0);
		return false; 
	}
}