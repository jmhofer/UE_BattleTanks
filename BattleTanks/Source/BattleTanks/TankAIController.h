// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	ATank* GetPlayerTank() const;

	void BeginPlay() override;
	void Tick(float) override;

	float AcceptanceRadius = -1.f;
};
