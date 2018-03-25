// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Tank = GetControlledTank();

	if (!Tank) {
		UE_LOG(LogTemp, Error, TEXT("not possessing any tank!"))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("possessing tank: %s"), *Tank->GetName())
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
