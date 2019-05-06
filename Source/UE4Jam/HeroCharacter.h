// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeroCharacter.generated.h"

UCLASS()
class UE4JAM_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacking")
		class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Attacking")
		float BaseDamage = 10.0f;

	UFUNCTION(BlueprintCallable, Category = "Attacking")
		void AttackTarget();

	UFUNCTION(BlueprintCallable, Category = "Attacking")
		void DealDamageToTarget(AActor* TargetActor);

private:
	class UAnimInstance* AnimInstance;
};
