// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_ConsumableItemBase.h"

// Sets default values
ADOTK_ConsumableItemBase::ADOTK_ConsumableItemBase()
{

}

void ADOTK_ConsumableItemBase::Use(class ADOTK_PlayerCharacter* Character)
{
	if (Character)
	{
		Character->GetHealthComponent()->AddToCurrentHealth(HealthToHeal);
		Character->GetHungerThirstComponent()->AddToCurrentHunger(HungerValue);
		Character->GetHungerThirstComponent()->AddToCurrentSaturation(SaturationValue);
		Character->GetHungerThirstComponent()->AddToCurrentThirst(ThirstValue);

		if (OwningInventory)
		{
			OwningInventory->RemoveFromInventory(this);
		}
	}
}