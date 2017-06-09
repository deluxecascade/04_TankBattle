// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))	{ return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::DelegateDeathMethod);
	}
}

void ATankAIController::DelegateDeathMethod()
{
	PossessedTank->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerTank)
	{
		// TODO Move towards the playyer
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm

		// Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// TODO Fix Fire if ready
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire(); //TODO limit firerate
		}
	}
}


	

