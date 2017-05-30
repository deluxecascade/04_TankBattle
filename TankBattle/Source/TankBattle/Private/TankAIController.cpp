// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AIControlledTank = GetTankAIController();
	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find AIControlledTank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI has possession of: %s"), *(AIControlledTank->GetName()));
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI can't find the player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI has determined human player tank is: %s"), *(PlayerTank->GetName()));
	}
}

ATank* ATankAIController::GetTankAIController() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}