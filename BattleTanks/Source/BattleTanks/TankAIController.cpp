// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "Navigation/PathFollowingComponent.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GetWorld() && GetPlayerTank())) { return; }

	AimingComponent = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto ControlledTank = Cast<ATank>(GetPawn());

	if (!ensure(ControlledTank && GetPlayerTank())) { return; }

	MoveToActor(GetPlayerTank(), AcceptanceRadius);
	AimingComponent->AimAt(GetPlayerTank()->GetActorLocation());
	AimingComponent->Fire();
}

ATank* ATankAIController::GetPlayerTank() const
{
	if (!ensure(GetWorld())) { return nullptr; }

	auto PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!ensure(PlayerController)) { return nullptr; }

	return PlayerController->GetControlledTank();
}
