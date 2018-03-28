// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

UTankAimingComponent* ATank::GetAimingComponent()
{
	return FindComponentByClass<UTankAimingComponent>();
}


void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;

	if (!ensure(GetWorld())) { return; }

	if (!IsReloaded) { return; }

	/*
	auto ProjectileLocation = GetAimingComponent()->Barrel->GetSocketLocation(FName("Projectile"));
	auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, ProjectileLocation, ProjectileRotation);

	if (!Projectile) {
		return;
	}

	Projectile->LaunchProjectile(LaunchSpeed);
	*/

	LastFireTime = FPlatformTime::Seconds();
}

void ATank::AimAt(FVector AimLocation)
{
	GetAimingComponent()->AimAt(AimLocation, LaunchSpeed);
}
