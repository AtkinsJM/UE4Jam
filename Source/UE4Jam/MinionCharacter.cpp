// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AMinionCharacter::AMinionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinionCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void AMinionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinionCharacter::AttackTarget()
{
	if (AttackMontages.Num() == 0) { return; }
	int8 MontageIndex = FMath::RandRange(0, AttackMontages.Num() - 1);
	UAnimMontage* AttackMontage = AttackMontages[MontageIndex];
	if (AnimInstance != nullptr && AttackMontage != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Minion attacked w/ animation"));
		AnimInstance->Montage_Play(AttackMontage, 1.f);
	}
}

void AMinionCharacter::DealDamageToTarget(AActor * TargetActor)
{
	if (TargetActor == nullptr) { return; }
	UGameplayStatics::ApplyDamage(TargetActor, Damage, GetController(), this, UDamageType::StaticClass());
}

