// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativeSpeed)
{
	//move the barrel the right amount this frame
	// Given a max elevation speed, and theframe time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	UE_LOG(LogTemp, Warning, TEXT("ElevationChange: %f at %f"), ElevationChange, GetWorld()->DeltaTimeSeconds)
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
