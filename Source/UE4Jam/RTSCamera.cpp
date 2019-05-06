// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCamera.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#define OUT

ARTSCamera::ARTSCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = GetCameraComponent();
}
//TODO decide if I need these methods - if not, remove
void ARTSCamera::BeginPlay()
{
}

void ARTSCamera::Tick(float DeltaTime)
{
	
}

void ARTSCamera::ZoomCamera(float AxisValue)
{
	if (CameraComponent == nullptr) { return; }
	float ZoomAmount = AxisValue * ZoomSpeed;
	FVector CurrentLocation = CameraComponent->GetRelativeTransform().GetLocation();
	FVector NewLocation = CurrentLocation + FVector(ZoomAmount, 0, 0);
	NewLocation = FVector(FMath::Clamp(NewLocation.X, MinZoom, MaxZoom), NewLocation.Y, NewLocation.Z);
	CameraComponent->SetRelativeLocation(NewLocation);
}

void ARTSCamera::ScrollCamera(float MouseX, float MouseY, int32 ViewPortX, int32 ViewPortY)
{
	int8 MoveCameraX = 0;
	int8 MoveCameraY = 0;
	if (MouseY < ActivePixelsFromEdge)
	{
		MoveCameraX = 1;
	}
	else if (MouseY > (ViewPortY - ActivePixelsFromEdge))
	{
		MoveCameraX = -1;
	}
	if (MouseX < ActivePixelsFromEdge)
	{
		MoveCameraY = -1;
	}
	else if (MouseX > (ViewPortX - ActivePixelsFromEdge))
	{
		MoveCameraY = 1;
	}
	FVector MovementVector = FVector(MoveCameraX, MoveCameraY, 0);
	MovementVector.Normalize();
	FVector NewLocation = GetActorLocation() + MovementVector * ScrollSpeed;
	NewLocation = FVector(FMath::Clamp(NewLocation.X, MinX, MaxX),FMath::Clamp(NewLocation.Y, MinY, MaxY), NewLocation.Z);
	SetActorLocation(NewLocation);
}
