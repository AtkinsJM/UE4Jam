// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPlacementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4JAM_API UActorPlacementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorPlacementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TArray<TSubclassOf<class APlaceableActor>> ActorsToPlace;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float TraceDepth = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float RotationSpeed = 10.0f;

	TSubclassOf<AActor> CurrentActorToPlace;
	
	void RotateSpawnedActor(float Value);

	void BindInput(class UInputComponent* InputComponent);

private:
	class ARTSPlayerController* Controller;

	void RaycastFromCursor();
	void SpawnActor();
	

	bool IsOccupied(FVector Location);

	int32 UnlockedActorFlags;

	class APlaceableActor* SpawnedActor = nullptr;
	FVector DefaultLocation = FVector(-1000, -1000, -1000);

	void UnlockActor(int32 Index);
};
