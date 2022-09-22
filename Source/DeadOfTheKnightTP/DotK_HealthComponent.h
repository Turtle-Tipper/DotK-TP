// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DotK_HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDotK_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDotK_HealthComponent();

	/* Maximum health of entity. Applicable for creatures and breakable objects. */
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHP = 100;

	/* Current health of entity. Applicable for creatures and breakable objects. */
	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHP = MaxHP;

	/* Additive value that increases the health gained from each regen tick. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float HealthRegenModifier = 1.0f;

	/* Time in seconds between each health regeneration. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float HealthRegenInterval = 3.0f;

	/* Keeps track of life status. */
	UPROPERTY(EditAnywhere, Category = "Health")
	bool bIsAlive = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartRegenHealth();

	UFUNCTION(BlueprintCallable)
	void EndRegenHealth();

	UFUNCTION(BlueprintCallable)
	void RequestIncreaseMaxHealth();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	// ** GETTER FUNCTIONS ** //

	UFUNCTION(BlueprintPure)
	float GetCurrentHP() { return CurrentHP; }

	UFUNCTION(BlueprintPure)
	float GetMaxHP() { return MaxHP; }

	UFUNCTION(BlueprintPure)
	float GetHPPercentage() { return CurrentHP / MaxHP; }

};
