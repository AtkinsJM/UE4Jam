// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "RTSCamera.generated.h"

/**
 * 
 */
UCLASS()
class UE4JAM_API ARTSCamera : public ACameraActor
{
	GENERATED_BODY()
	
protected:


public:
	ARTSCamera();

	UPROPERTY(EditAnywhere, Category = "Setup")
		float ActivePixelsFromEdge = 50.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float ScrollSpeed = 50.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float ZoomSpeed = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinZoom = -200.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxZoom = 200.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinX = -1500.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxX = 2000.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinY = -1000.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxY = 2000.0f;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void ZoomCamera(float AxisValue);
	UFUNCTION(BlueprintCallable)
		void ScrollCamera(float MouseX, float MouseY, int32 ViewPortX, int32 ViewPortY);

private:
	class UCameraComponent* CameraComponent;
};
