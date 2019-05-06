// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPlacementComponent.h"
#include "Engine/World.h"
#include "RTSPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlaceableActor.h"

#define ECC_Ground ECollisionChannel::ECC_GameTraceChannel2

// Sets default values for this component's properties
UActorPlacementComponent::UActorPlacementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorPlacementComponent::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<ARTSPlayerController>(GetOwner());
	CurrentActorToPlace = ActorsToPlace[0];
	UnlockActor(0);
	UnlockActor(1);
	//TODO SET UP INPUT SYSTEM FOR SPAWNING
	//SpawnActor();
}


// Called every frame
void UActorPlacementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (CurrentActorToPlace == nullptr) { return; }
	if (SpawnedActor != nullptr)
	{
		RaycastFromCursor();
	}
}

void UActorPlacementComponent::RotateSpawnedActor(float Value)
{
	if (SpawnedActor == nullptr) { return; }
	if (Value == 0) { return; }
	FRotator CurrentRotation = SpawnedActor->GetActorRotation();
	FRotator NewRotation = CurrentRotation + FRotator(0, Value, 0) * RotationSpeed;
	SpawnedActor->SetActorRotation(NewRotation);
}

void UActorPlacementComponent::BindInput(UInputComponent * InputComponent)
{
	InputComponent->BindAction("Spawn Actor", IE_Pressed, this, &UActorPlacementComponent::SpawnActor);
}

void UActorPlacementComponent::RaycastFromCursor()
{
	if (Controller == nullptr) { return; }
	FHitResult Hit;
	if (Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel2, false, OUT Hit))
	{
		SpawnedActor->SetActorLocation(Hit.Location);
		if (!IsOccupied(Hit.Location))
		{
			if (Controller->IsInputKeyDown(EKeys::LeftMouseButton))
			{
				SpawnedActor->MakeActorSolid();
				SpawnedActor = nullptr;
				return;
			}
		}
		if (Controller->IsInputKeyDown(EKeys::RightMouseButton))
		{
			SpawnedActor->Destroy();
			SpawnedActor = nullptr;
			return;
		}
	}
	else
	{
		SpawnedActor->SetActorLocation(DefaultLocation);
	}
}

void UActorPlacementComponent::SpawnActor()
{
	// If already has spawned actor in hand, return
	if (SpawnedActor != nullptr) { return; }
	int32 ActorIndex = -1;
	if (Controller->IsInputKeyDown(EKeys::One))
	{
		ActorIndex = 0;
	}
	else if (Controller->IsInputKeyDown(EKeys::Two))
	{
		ActorIndex = 1;
	}
	else if (Controller->IsInputKeyDown(EKeys::Three))
	{
		ActorIndex = 2;
	}
	// Check if valid index
	if (ActorIndex >= ActorsToPlace.Num() || ActorsToPlace.Num() == 0 || ActorIndex < 0) { return; }
	int32 BinSequence = FMath::Pow(2, ActorIndex);
	// Check if selected actor is unlocked
	if ((UnlockedActorFlags & BinSequence) != BinSequence) { return; }
	FActorSpawnParameters ActorSpawnParams;
	SpawnedActor = GetWorld()->SpawnActor<APlaceableActor>(ActorsToPlace[ActorIndex], ActorSpawnParams);
	SpawnedActor->MakeActorEthereal();
}

bool UActorPlacementComponent::IsOccupied(FVector Location)
{
	FHitResult HitResult;
	FVector ActorExtents = SpawnedActor->GetActorExtents();
	FVector Origin = Location + FVector(0, 0, ActorExtents.Z);
	ETraceTypeQuery TracyQuery = UEngineTypes::ConvertToTraceType(ECC_WorldDynamic);
	bool bHasHit = UKismetSystemLibrary::BoxTraceSingle(
		this,
		Origin,
		Origin - FVector(0, 0, TraceDepth),
		FVector(ActorExtents.X, ActorExtents.Y, ActorExtents.Z),
		SpawnedActor->GetActorRotation(),
		TracyQuery,
		false,
		TArray<AActor*>{SpawnedActor},
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red
	);
	return bHasHit;
}

void UActorPlacementComponent::UnlockActor(int32 Index)
{
	int32 BinSequence = FMath::Pow(2, Index);
	UnlockedActorFlags |= BinSequence;
}


