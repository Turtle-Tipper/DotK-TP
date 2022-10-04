// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeadOfTheKnightTPCharacter.h"
#include "DOTK_HungerThirstComponent.h"
#include "DOTK_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_PlayerCharacter : public ADeadOfTheKnightTPCharacter
{
	GENERATED_BODY()

	/* Hunger and Thirst Component */
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = HungerAndThirst, meta = (AllowPrivateAccess = "true"))
	class UDOTK_HungerThirstComponent* HungerThirstComponent;

public:

	ADOTK_PlayerCharacter();

protected:

	virtual void Tick(float DeltaTime) override;

	// ** STAMINA FUNCTIONS ** //

	/* Called to drain stamina. */
	UFUNCTION(BlueprintCallable)
	void DrainStamina();

	/* Called to rest stamina regen logic. */
	UFUNCTION(BlueprintCallable)
	void EnableStaminaRegen();

	/* Called to perform actions to character once stamina is fully depleted (stun them, have regen delay, etc). */
	UFUNCTION(BlueprintCallable)
	void DepletedAllStamina();



protected:

	// ** STAMINA ** //

	/* Keeps track of whether character Stamina can currently regen. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	bool bCanRegenStamina;

	/* The current amount of Stamina the character has. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float CurrentStamina = 100.0f;

	/* The highest value a character's Stamina regens to. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float MaxStamina = 100.0f;

	/* The value of stamina to be drained. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float SprintStaminaDrain = 5.0f;

	/* Interval in seconds at which Stamina is drained. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float DrainInterval = 1.0f;

	/* The increment at which Stamina is regenerated. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaRegen = 8.0f;

	/* Interval in seconds at which Stamina is regenerated. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float RegenInterval = 1.0f;

	/* Stamina regen timer handle. */
	FTimerHandle StaminaRegenTimerHandle;

	// ** SPRINT ** //

	/* Value that determines the max speed a player can sprint. */
	UPROPERTY(EditAnywhere, Category = "Character Movement")
	float MaxSprintSpeed = 1500.0f;

	/* The time after using Stamina before it begins to regenerate. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaRegenDelay = 1.5f;

	/* Character Reference. */

	// ** DEBUG ** //

	/* Hunger amount applied by pressing F. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingEatAmount = 25.0f;

	/* Applied when testing hunger. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingSaturationAmount = 25.0f;

	/* Thirst amount applied by pressing T. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingDrinkAmount = 25.0f;

public:

	// ** HUNGER AND THIRST FUNCTIONS ** //

	UFUNCTION(BlueprintCallable)
	void RequestEat();

	UFUNCTION(BlueprintCallable)
	void RequestDrink();

	UFUNCTION(BlueprintCallable)
	void RequestEmptyHungerThirst();

	virtual void RequestSprintStart() override;
	virtual void RequestSprintStop() override;

	/* GETTER FUNCTIONS */

	UFUNCTION(BlueprintPure)
	float GetCurrentStaminaPercent() { return CurrentStamina / MaxStamina; }

	float GetMaxStamina() { return MaxStamina; }

	/** Returns HungerThirstComponent subobject **/
	FORCEINLINE class UDOTK_HungerThirstComponent* GetHungerThirstComponent() const { return HungerThirstComponent; }
	
};
