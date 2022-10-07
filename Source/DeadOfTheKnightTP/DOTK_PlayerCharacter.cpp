// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_PlayerCharacter.h"

ADOTK_PlayerCharacter::ADOTK_PlayerCharacter()
{
	// ** COMPONENT CREATION ** //


	// Create a hunger and thirst component
	HungerThirstComponent = CreateDefaultSubobject<UDOTK_HungerThirstComponent>(TEXT("HungerHealthComponent"));

	// Create a level handler component
	LevelHandlerComponent = CreateDefaultSubobject<UDOTK_LevelHandlerComponent>(TEXT("LevelHandlerComponent"));
}

void ADOTK_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrainStamina(DeltaTime);

	if (GetHungerThirstComponent()->GetIsStarving() == true)
	{
		// if the character is starving, pass in the current HP regen to the starving regen value.
		GetHealthComponent()->RegenerateHealth(DeltaTime, GetHealthComponent()->GetStarvingHealthRegen());
	}
	else if (GetHungerThirstComponent()->GetIsStarving() == false)
	{
		// if the character is not starving, pass in the current HP regen to the max regen value.
		GetHealthComponent()->RegenerateHealth(DeltaTime, GetHealthComponent()->GetMaxHealthRegen());
	}

	GetHungerThirstComponent()->DrainHunger(DeltaTime);
	GetHungerThirstComponent()->DrainThirst(DeltaTime);
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

void ADOTK_PlayerCharacter::DrainStamina(float DeltaTime)
{
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

// ** ITEMS ** //

void ADOTK_PlayerCharacter::PickupItem()
{
	if (bIsOverlappingItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("We picked up an item."))
	}
}

void ADOTK_PlayerCharacter::AddToInventory(ADOTK_ItemBase* Item)
{
	// check to make sure an item is passed in, if not UE_LOG and return
	if (!Item) { UE_LOG(LogTemp, Warning, TEXT("Item to add returning null.")) return; }

	// get inventory struct, get ItemList array and add item to array.
	Inventory.ItemList.Add(Item);
}