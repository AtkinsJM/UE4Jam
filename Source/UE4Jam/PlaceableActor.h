// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableActor.generated.h"

UCLASS()
class UE4JAM_API APlaceableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetActorExtents();
	void MakeActorSolid();
	void MakeActorEthereal();

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AActor> ReplacementActor;

private:
	FVector ActorExtents = FVector::ZeroVector;
};
