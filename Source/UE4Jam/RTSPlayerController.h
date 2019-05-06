// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4JAM_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSPlayerController();

	class UActorPlacementComponent* ActorPlacementComponent;
	
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

private:
	void GetMousePositionAndScrollCamera();

	class ARTSCamera* RTSCamera;

	void ZoomCamera(float AxisValue);

	void RotateActor(float AxisValue);
};
