// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float DegreesPerSecond)
{
	//move the barrel the right amount this frame
	// Given a max elevation speed, and theframe time
	UE_LOG(LogTemp, Warning, TEXT("Elevate has been called at speed: %f"), DegreesPerSecond)
}
