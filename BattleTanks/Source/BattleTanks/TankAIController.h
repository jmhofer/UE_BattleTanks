// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	UTankAimingComponent * AimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 5000.f;

	APawn* GetPlayerTank() const;

	void BeginPlay() override;
	void Tick(float) override;

};
