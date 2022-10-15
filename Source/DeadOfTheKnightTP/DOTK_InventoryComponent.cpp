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


// Called every frame
void UDOTK_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDOTK_InventoryComponent::AddToInventory(ADOTK_ItemBase* Item)
{
	// check to make sure an item is passed in, if not UE_LOG and return
	if (!Item) { UE_LOG(LogTemp, Warning, TEXT("Item to add returning null.")) return; }

	// get inventory struct, get ItemList array and add item to array.
	// in player character version, inventory was all in struct, so you needed to go into the instance of the struct that was named Inventory
	// FInventory Inventory
	ItemList.Add(Item);
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