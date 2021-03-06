// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// In Newtons assuming 40000kg at 1g acceleration
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000;



private:
	/*virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;*/

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysForce();

	void DriveTrack();

	float CurrentThrottle = 0;
};
