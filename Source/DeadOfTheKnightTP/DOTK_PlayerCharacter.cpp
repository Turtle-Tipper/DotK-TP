// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_PlayerCharacter.h"

ADOTK_PlayerCharacter::ADOTK_PlayerCharacter()
{
	// ** COMPONENT CREATION ** //


	// Create a hunger and thirst component
	HungerThirstComponent = CreateDefaultSubobject<UDOTK_HungerThirstComponent>(TEXT("HungerHealthComponent"));
}

void ADOTK_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Sprint Stamina drain functionality
	if (bIsSprinting)
	{
		CurrentStamina = FMath::FInterpConstantTo(CurrentStamina, 0.0f, DeltaTime, SprintStaminaDrain);

		if (GetHungerThirstComponent()->GetIsDehydrated() == true)
		{
			RequestSprintStop();
		}
		if (CurrentStamina <= 0.0f)
		{
			DepletedAllStamina();
		}
	}
	else
	{
		if (CurrentStamina < MaxStamina)
		{
			if (bCanRegenStamina)
			{
				CurrentStamina = FMath::FInterpConstantTo(CurrentStamina, MaxStamina, DeltaTime, StaminaRegen);
			}
		}
	}
}

// ** CHARACTER MOVEMENT ** //

void ADOTK_PlayerCharacter::RequestSprintStart()
{
	if (GetHungerThirstComponent()->GetIsDehydrated() == false)
	{
		if (CurrentStamina > 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = GetSprintSpeed();
			bIsSprinting = true;

			// Stop Stamina regen for a short period
			bCanRegenStamina = false;
			GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTimerHandle);
		}
	}
}

void ADOTK_PlayerCharacter::RequestSprintStop()
{
	if (bIsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = GetWalkSpeed();
		bIsSprinting = false;

		// Start timer to regen stamina when character has stopped sprinting
		GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimerHandle, this, &ADOTK_PlayerCharacter::EnableStaminaRegen, StaminaRegenDelay, false);
	}
}

// ** STAMINA ** //

void ADOTK_PlayerCharacter::DrainStamina()
{

}

void ADOTK_PlayerCharacter::EnableStaminaRegen()
{
	bCanRegenStamina = true;
}

void ADOTK_PlayerCharacter::DepletedAllStamina()
{
	RequestSprintStop();
}

// ** HUNGER AND THIRST ** //

void ADOTK_PlayerCharacter::RequestEat()
{
	GetHungerThirstComponent()->Eat(TestingEatAmount, TestingSaturationAmount);
}

void ADOTK_PlayerCharacter::RequestDrink()
{
	GetHungerThirstComponent()->Drink(TestingDrinkAmount);
}

void ADOTK_PlayerCharacter::RequestEmptyHungerThirst()
{
	GetHungerThirstComponent()->SetCurrentSaturation(0.0f);
	GetHungerThirstComponent()->SetCurrentHunger(0.0f);
	GetHungerThirstComponent()->SetCurrentThirst(0.0f);
}