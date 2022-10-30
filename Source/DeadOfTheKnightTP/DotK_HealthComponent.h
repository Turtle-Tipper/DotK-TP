// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DotK_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageReceivedDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDotK_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDotK_HealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Logic for health regeneration. Called in PlayerCharacter tick.
	void RegenerateHealth(float DeltaTime, float RegenLevel);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable)
	void Kill();

	UFUNCTION(BlueprintCallable)
	void Revive(float HealthToRezWith);

	// ** GETTER FUNCTIONS ** //

	bool GetIsAlive() { return bIsAlive; }

	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() { return CurrentHealth; }

	UFUNCTION(BlueprintPure)
	float GetMaxHealth() { return MaxHealth; }

	UFUNCTION(BlueprintPure)
	float GetStarvingHealthRegen() { return StarvationHealthRegen; }

	UFUNCTION(BlueprintPure)
	float GetCurrentHealthRegen() { return CurrentHealthRegen; }

	UFUNCTION(BlueprintPure)
	float GetMaxHealthRegen() { return MaxHealthRegen; }

	UFUNCTION(BlueprintPure)
	float GetHPPercentage() { return CurrentHealth / MaxHealth; }

	// ** SETTER FUNCTIONS ** //

	UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(float HPAmount) { CurrentHealth = HPAmount; }

	UFUNCTION(BlueprintCallable)
	void SetCurrentHealthRegen(float CurrentRegenAmount) { CurrentHealthRegen = CurrentRegenAmount; }

	UFUNCTION(BlueprintCallable)
	void SetMaxHealthRegen(float MaxRegenAmount) { MaxHealthRegen = MaxRegenAmount; }


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void EnableHealthRegen();

	UFUNCTION(BlueprintCallable)
	void RequestIncreaseMaxHealth();

	/* Keeps track of life status. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsAlive = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bHasTakenDamage = false;

	/* Keeps track of whether entity can regen health. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	bool bCanRegenHealth;

	/* Maximum health of entity. Applicable for creatures and breakable objects. */
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100;

	/* Current health of entity. Applicable for creatures and breakable objects. */
	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHealth = MaxHealth;

	/* Rate at which health is drained while starving. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	float StarvationHealthDrain = 1.0f;

	/* Max Regen HP while starving. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float StarvationHealthRegen = 30.0f;

	/* Current amount of health that can be regenerated to. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float CurrentHealthRegen = MaxHealthRegen;

	/* Maximum amount of health the player can naturally regenerate to. */
	UPROPERTY(EditAnywhere, Category = "Regen")
	float MaxHealthRegen = 70.0f;

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
	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeathDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDamageReceivedDelegate OnDamageReceivedDelegate;
};
