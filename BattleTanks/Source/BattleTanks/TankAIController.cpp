// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Navigation/PathFollowingComponent.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GetWorld() && GetPlayerTank())) { return; }

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!ensure(AimingComponent && GetPlayerTank())) { return; }

	MoveToActor(GetPlayerTank(), AcceptanceRadius);
	AimingComponent->AimAt(GetPlayerTank()->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}
}

APawn* ATankAIController::GetPlayerTank() const
{
	if (!ensure(GetWorld())) { return nullptr; }

	auto PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!ensure(PlayerController)) { return nullptr; }

	return PlayerController->GetPawn();
}
