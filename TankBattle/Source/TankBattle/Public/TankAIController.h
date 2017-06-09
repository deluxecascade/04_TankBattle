// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"


class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY (EditDefaultsOnly, Category = "Movement")
	float AcceptanceRadius = 8000;

	UFUNCTION()
	void DelegateDeathMethod();

	ATank* PossessedTank = nullptr;

};
