// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DOTK_HungerThirstComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDOTK_HungerThirstComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UDOTK_HungerThirstComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void EnableHungerDrain();

	void EnableThirstDrain();

	void EnableStarvation();

	void EnableDehydration();

	// ** HUNGER VARIABLES ** //

	/* Keeps track of whether it has been long enough since eating for hunger to drain. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	bool bCanDrainHunger = true;

	/* Keeps track of whether the player is starving. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	bool bIsStarving = false;

	/* Max Hunger value for a character. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	float MaxHunger = 100.0f;

	/* Current Hunger value for a character. Clamped between 0 and MaxHunger. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	float CurrentHunger = MaxHunger / 2;

	/* Rate at which hunger drains. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	float HungerDrain = 0.2f;

	/* Max Saturation value for a character. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	float MaxSaturation = 100.0f;

	/* Current Saturation value for a character. Clamped between 0 and MaxSaturation. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	float CurrentSaturation = MaxSaturation / 2;

	/* Time in seconds after eating before hunger can start to drain. */
	UPROPERTY(EditAnywhere, Category = "Hunger")
	float HungerDrainDelay = 120.0f;

	FTimerHandle HungerDrainTimerHandle;

	// ** THIRST VARIABLES ** //

	/* Keeps track of whether it has been long enough since drinking for thirst to drain. */
	UPROPERTY(EditAnywhere, Category = "Thirst")
	bool bCanDrainThirst = true;

	/* Keeps track of whether the player is dehydrated. */
	UPROPERTY(EditAnywhere, Category = "Thirst")
	bool bIsDehydrated = false;

	/* Max Thirst value for a character. */
	UPROPERTY(EditAnywhere, Category = "Thirst")
	float MaxThirst = 100.0f;

	/* Current Thirst value for a character. Clamped between 0 and MaxThirst. */
	UPROPERTY(EditAnywhere, Category = "Thirst")
	float CurrentThirst = MaxThirst / 2;

	/* Rate at which thirst drains. */
	UPROPERTY(EditAnywhere, Category = "Thirst")
	float ThirstDrain = 0.02;

	/* Time in seconds after drinking before thirst can start to drain. */
	UPROPERTY(EditAnywhere, Category = "Thirst")
	float ThirstDrainDelay = 600.0f;

	FTimerHandle ThirstDrainTimerHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Eat(float HungerValue, float SaturationValue);

	void Drink(float ThirstValue);

	// ** GETTERS ** //

	UFUNCTION(BlueprintPure, Category = "Hunger")
	float GetHungerPercentage() { return CurrentHunger / MaxHunger; }

	UFUNCTION(BlueprintPure, Category = "Hunger")
	float GetSaturationPercentage() { return CurrentSaturation / MaxSaturation; }

	UFUNCTION(BlueprintPure, Category = "Thirst")
	float GetThirstPercentage() { return CurrentThirst / MaxThirst; }

	UFUNCTION(BlueprintPure, Category = "Hunger")
	bool GetIsStarving() { return bIsStarving; }

	UFUNCTION(BlueprintPure, Category = "Thirst")
	bool GetIsDehydrated() { return bIsDehydrated; }

	// ** SETTERS ** //

	UFUNCTION(BlueprintCallable, Category = "Hunger")
	void SetCurrentHunger(float HungerAmount) { CurrentHunger = HungerAmount; }

	UFUNCTION(BlueprintCallable, Category = "Hunger")
	void SetCurrentSaturation(float SaturationAmount) { CurrentSaturation = SaturationAmount; }
	
	UFUNCTION(BlueprintCallable, Category = "Thirst")
	void SetCurrentThirst(float ThirstAmount) { CurrentThirst = ThirstAmount; }
};
