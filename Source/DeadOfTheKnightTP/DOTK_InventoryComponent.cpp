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

	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UDOTK_InventoryComponent::RemoveFromInventory(ADOTK_ItemBase* Item)
{
	if (Item)
	{
		Item->SetOwningInventory(nullptr);
		Item->World = nullptr;
		ItemList.RemoveSingle(Item);
		// Update UI
		OnInventoryUpdated.Broadcast();
		return true;
	}

	return false;
}

bool UDOTK_InventoryComponent::HasWeightLimit()
{
	if (WeightLimit)
	{
		return true;
	}
	else
	{
		return false;
	}
}