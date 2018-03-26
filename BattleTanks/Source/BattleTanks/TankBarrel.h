// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Hold barrel properties
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0.f;
};
