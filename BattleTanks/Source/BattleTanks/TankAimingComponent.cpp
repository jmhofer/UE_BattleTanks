// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmunition;
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentAmmo <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	} else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds) {
		FiringState = EFiringState::Reloading;
	} else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	} else {
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return true; }

	return (!AimDirection.Equals(Barrel->GetForwardVector(), 0.01f));
}

void UTankAimingComponent::InitialiseComponent(UTankBarrel* Barrel, UTankTurret* Turret)
{
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, 
		false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace)) {

		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto DeltaRotator = AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();
	Barrel->Elevate(DeltaRotator.Pitch);

	auto Yaw = (FMath::Abs(DeltaRotator.Yaw) < 180.f) ? DeltaRotator.Yaw : -DeltaRotator.Yaw;
	Turret->Rotate(Yaw);
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::OutOfAmmo || FiringState == EFiringState::Reloading) { return; }

	if (!ensure(GetWorld() && ProjectileBluePrint)) { return; }

	auto ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, ProjectileLocation, ProjectileRotation);

	if (!ensure(Projectile)) { return; }

	Projectile->LaunchProjectile(LaunchSpeed);

	LastFireTime = FPlatformTime::Seconds();
	CurrentAmmo--;
}
