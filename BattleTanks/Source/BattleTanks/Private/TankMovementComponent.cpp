// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"

void UTankMovementComponent::InitialiseComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack) {
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("intend move forward: %f"), Throw);
	// TODO
}
