// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 MaxHealth = 100;

	int32 CurrentHealth = 0;
};
