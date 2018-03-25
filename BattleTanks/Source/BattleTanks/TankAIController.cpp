// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto Tank = GetControlledTank();

	if (!GetWorld()) {
		UE_LOG(LogTemp, Error, TEXT("%s has no access to the game world!"), *GetName())
	}

	if (!Tank) {
		UE_LOG(LogTemp, Error, TEXT("%s not possessing any tank!"), *GetName())
	} else {
		UE_LOG(LogTemp, Warning, TEXT("%s possessing tank: %s"), *GetName(), *Tank->GetName())
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("%s unable to find the player tank!"), *GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s found the player tank: %s"), *GetName(), *PlayerTank->GetName())
	}
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
