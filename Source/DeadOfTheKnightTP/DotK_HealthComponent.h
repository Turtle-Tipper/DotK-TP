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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void EnableHealthRegen();

	UFUNCTION(BlueprintCallable)
	void RequestIncreaseMaxHealth();

	/* Keeps track of life status. */
	UPROPERTY(EditAnywhere, Category = "Health")
	bool bIsAlive = true;

	/* Keeps track of whether entity can regen health. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	bool bCanRegenHealth;

	/* Maximum health of entity. Applicable for creatures and breakable objects. */
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHP = 100;

	/* Current health of entity. Applicable for creatures and breakable objects. */
	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHP = MaxHP;

	/* Maximum amount of health the player can naturally regenerate to. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float MaxRegenHP = 70.0f;

	/* Amount of health regenerated for each regen interval. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float HealthRegenAmount = 1.0f;

	/* Time in seconds between each health regeneration. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float HealthRegenInterval = 3.0f;

	/* Time in seconds after taking damage before health regen can start. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float HealthRegenDelay = 8.0f;

	FTimerHandle HealthRegenTimerHandle;

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
	float GetMaxRegenHP() { return MaxRegenHP; }

	UFUNCTION(BlueprintPure)
	float GetHPPercentage() { return CurrentHP / MaxHP; }

	// ** SETTER FUNCTIONS ** //

	UFUNCTION(BlueprintCallable)
	void SetCurrentHP(float HPAmount) { CurrentHP = HPAmount; }

	UFUNCTION(BlueprintCallable)
	void SetMaxRegenHP(float MaxRegenAmount) { MaxRegenHP = MaxRegenAmount; }

};
