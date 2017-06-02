// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto AIControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
		
	if (PlayerTank)
	{
		// TODO Move towards the playyer
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm

		// Aim towards the player
		AIControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		AIControlledTank->Fire(); //TODO limit firerate
	}
}


	

