// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) {
		UE_LOG(LogTemp, Error, TEXT("%s: unable to find world"), *GetName())
	}

	if (!GetControlledTank()) {
		UE_LOG(LogTemp, Error, TEXT("%s: unable to find controlled tank"), *GetName())
	}

	if (!GetPlayerTank()) {
		UE_LOG(LogTemp, Error, TEXT("%s unable to find the player tank!"), *GetName())
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!GetControlledTank() || !GetPlayerTank()) {
		return;
	}

	// TODO move towards player

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

	// TODO fire when ready
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

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
