// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	auto ClampedDamage = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= ClampedDamage;

	UE_LOG(LogTemp, Warning, TEXT("Damage applied: %f, damage received: %d, current health: %d"), Damage, ClampedDamage, CurrentHealth)

	return ClampedDamage;
}
