// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	auto Force = Throttle * GetForwardVector() * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(Force, ForceLocation);
}
