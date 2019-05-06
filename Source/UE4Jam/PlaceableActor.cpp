// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableActor.h"
#include "Engine/World.h"

// Sets default values
APlaceableActor::APlaceableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlaceableActor::BeginPlay()
{
	Super::BeginPlay();
	FVector Origin;
	GetActorBounds(true, OUT Origin, OUT ActorExtents);
}

// Called every frame
void APlaceableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector APlaceableActor::GetActorExtents()
{
	return ActorExtents;
}

void APlaceableActor::MakeActorSolid()
{
	SetActorEnableCollision(true);
	if (ReplacementActor != nullptr)
	{
		FActorSpawnParameters ActorSpawnParams;
		GetWorld()->SpawnActor<AActor>(ReplacementActor, GetActorTransform(), ActorSpawnParams);
		Destroy();
	}
}

void APlaceableActor::MakeActorEthereal()
{
	SetActorEnableCollision(false);
}

