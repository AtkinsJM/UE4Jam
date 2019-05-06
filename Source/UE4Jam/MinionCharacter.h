// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MinionCharacter.generated.h"

UCLASS()
class UE4JAM_API AMinionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinionCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
		float Damage = 10.0f;

	UFUNCTION(BlueprintCallable, Category = "Attacking")
		void AttackTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacking")
		TArray<class UAnimMontage*> AttackMontages;

	UFUNCTION(BlueprintCallable, Category = "Attacking")
		void DealDamageToTarget(AActor* TargetActor);

private:
	class UAnimInstance* AnimInstance;

};
