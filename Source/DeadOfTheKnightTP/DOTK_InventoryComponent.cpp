// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_InventoryComponent.h"

// Sets default values for this component's properties
UDOTK_InventoryComponent::UDOTK_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDOTK_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UDOTK_InventoryComponent::AddToInventory(ADOTK_ItemBase* Item)
{
	// check to make sure an item is passed in, if not UE_LOG and return
	if (!Item) { UE_LOG(LogTemp, Warning, TEXT("Item to add returning null.")) return false; }

	if (ItemList.Num() >= SlotLimit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough space."));
		return false;
	}

	Item->SetOwningInventory(this);
	// having world allows spawning particles
	Item->World = GetWorld();
	// FInventory Inventory
	ItemList.Add(Item);
	// Add item's weight to current weight
	CurrentWeight += Item->GetItemWeight();

	// Encumbrance logic
	if (HasWeightLimit())
	{
		UpdateEncumbrance();
	}

	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UDOTK_InventoryComponent::RemoveFromInventory(ADOTK_ItemBase* Item)
{
	if (Item)
	{
		// set item data to null
		Item->SetOwningInventory(nullptr);
		Item->World = nullptr;
		// remove item from ItemList
		ItemList.RemoveSingle(Item);
		// subtract item's weight from current weight
		CurrentWeight -= Item->GetItemWeight();

		// Encumbrance logic
		if (HasWeightLimit())
		{
			UpdateEncumbrance();
		}
		

		// Update UI
		OnInventoryUpdated.Broadcast();
		return true;
	}

	return false;
}

void UDOTK_InventoryComponent::UpdateEncumbrance()
{
	if (CurrentWeight > WeightLimit)
	{
		bIsEncumbered = true;
		EncumbranceValue = CurrentWeight - WeightLimit;
		UE_LOG(LogTemp, Warning, TEXT("Inventory is now encumbered."));
	}
	else
	{
		bIsEncumbered = false;
		UE_LOG(LogTemp, Warning, TEXT("Inventory is not currently encumbered."));
	}
	OnEncumbranceUpdated.Broadcast();
}

bool UDOTK_InventoryComponent::HasWeightLimit()
{
	if (WeightLimit != 0.0f)
	{
		bHasWeightLimit = true;
	}
	else
	{
		bHasWeightLimit = false;
	}

	return bHasWeightLimit;
}