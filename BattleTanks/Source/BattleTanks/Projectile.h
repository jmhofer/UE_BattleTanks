// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UTankProjectileMovementComponent;

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UTankProjectileMovementComponent* TankProjectileMovementComponent = nullptr;

	virtual void Tick(float DeltaTime) override;
};
