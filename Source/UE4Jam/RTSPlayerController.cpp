// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "RTSCamera.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ActorPlacementComponent.h"

#define OUT
#define ECC_Ground ECollisionChannel::ECC_GameTraceChannel2

ARTSPlayerController::ARTSPlayerController()
{
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ActorPlacementComponent = FindComponentByClass<UActorPlacementComponent>();
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARTSCamera::StaticClass(), OUT FoundCameras);
	if (FoundCameras.Num() != 0)
	{
		RTSCamera = Cast<ARTSCamera>(FoundCameras[0]);
		SetViewTarget(RTSCamera);
	}	
}

void ARTSPlayerController::Tick(float DeltaTime)
{
	GetMousePositionAndScrollCamera();
	
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Camera Zoom", this, &ARTSPlayerController::ZoomCamera);
	InputComponent->BindAxis("Actor Rotation", this, &ARTSPlayerController::RotateActor);
	if (ActorPlacementComponent == nullptr)
	{
		ActorPlacementComponent = FindComponentByClass<UActorPlacementComponent>();
	}
	if (ActorPlacementComponent == nullptr) { return; }
	ActorPlacementComponent->BindInput(InputComponent);
}

void ARTSPlayerController::GetMousePositionAndScrollCamera()
{
	if (RTSCamera == nullptr) { return; }
	int32 ViewPortX;
	int32 ViewPortY;
	GetViewportSize(OUT ViewPortX, OUT ViewPortY);
	float MouseX;
	float MouseY;
	GetMousePosition(OUT MouseX, OUT MouseY);
	RTSCamera->ScrollCamera(MouseX, MouseY, ViewPortX, ViewPortY);
}

void ARTSPlayerController::ZoomCamera(float AxisValue)
{
	if (RTSCamera == nullptr) { return; }
	RTSCamera->ZoomCamera(AxisValue);
}


void ARTSPlayerController::RotateActor(float AxisValue)
{
	ActorPlacementComponent->RotateSpawnedActor(AxisValue);
}
