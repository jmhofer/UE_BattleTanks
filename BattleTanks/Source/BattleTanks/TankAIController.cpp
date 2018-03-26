// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) {
		UE_LOG(LogTemp, Error, TEXT("%s: unable to find world"), *GetName())
	}

	if (!GetPlayerTank()) {
		UE_LOG(LogTemp, Error, TEXT("%s unable to find the player tank!"), *GetName())
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto ControlledTank = Cast<ATank>(GetPawn());

	if (!ControlledTank || !GetPlayerTank()) {
		return;
	}

	// TODO move towards player

	ControlledTank->AimAt(GetPlayerTank()->GetActorLocation());

	// TODO fire only when ready
	ControlledTank->Fire();
}

ATank* ATankAIController::GetPlayerTank() const
{
	if (!GetWorld()) {
		return nullptr;
	}

	auto PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController) {
		return nullptr;
	}

	return PlayerController->GetControlledTank();
}
