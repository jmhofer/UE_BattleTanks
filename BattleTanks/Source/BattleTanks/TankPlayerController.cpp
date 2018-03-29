// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GetWorld() && GetPawn())) { return; }

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnDeath);
	}
}

void ATankPlayerController::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: DEAD EVENT RECEIVED"))
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { // e.g. when not possessing
		return;
	}
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;
	bool bHasHit = GetSightRayHitLocation(HitLocation);
	if (bHasHit) {
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D InScreenLocation, FVector& OutLookDirection) const {
	FVector _WorldLocation, WorldDirection;
	return DeprojectScreenPositionToWorld(InScreenLocation.X, InScreenLocation.Y, _WorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector InLookDirection, FVector &OutHitLocation) const
{
	if (!ensure(GetWorld() && PlayerCameraManager)) { return false; }

	auto LineTraceStart = PlayerCameraManager->GetTargetLocation();
	auto LineTraceEnd = LineTraceStart + LineTraceRange * InLookDirection;

	FHitResult HitResult;
	auto QueryParams = FCollisionQueryParams(FName(), false, GetPawn());
	auto HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_Visibility, QueryParams);

	OutHitLocation = HitResult.Location;
	return HasHit;
}
