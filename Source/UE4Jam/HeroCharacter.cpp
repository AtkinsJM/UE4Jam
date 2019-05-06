// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Perception/AISense_Hearing.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeroCharacter::AttackTarget()
{
	if (AnimInstance != nullptr && AttackMontage != nullptr)
	{
		AnimInstance->Montage_Play(AttackMontage, 1.f);
				
		//UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1.0f);
	}
}

void AHeroCharacter::DealDamageToTarget(AActor* TargetActor)
{
	if (TargetActor == nullptr) { return; }
	UGameplayStatics::ApplyDamage(TargetActor, BaseDamage, GetController(), this, UDamageType::StaticClass());
}

