// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_LootTableComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UDOTK_LootTableComponent::UDOTK_LootTableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDOTK_LootTableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDOTK_LootTableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<ADOTK_ItemBase*> UDOTK_LootTableComponent::CalculateDrops()
{
	// Create array of items to be dropped
	TArray<ADOTK_ItemBase*> DropArray;

	// Create array of names to iterate through
	TArray<FName> RowNames;
	RowNames = LootTable->GetRowNames();
	
	for (auto& name : RowNames)
	{
		// Get the row of the item to be rolled on
		FLootTableRow* Row = LootTable->FindRow<FLootTableRow>(FName(name), FString(""));
		
		if (Row)
		{
			// get a random number within range
			//TODO: be data driven to allow for influence from luck stat
			int Roll = FMath::RandRange(1, 100);

			// if roll is successful, add item of that row to DropArray
			if (Roll <= Row->DropChance)
			{
				// add item from current row in iteration to drop array
				ADOTK_ItemBase* Drop = Row->Item;
				DropArray.Add(Drop);
			}
		}
	}
	
	return DropArray;
}

int UDOTK_LootTableComponent::CalculateDropAmount()
{
	// Get the row of the item to be rolled on
	FLootTableRow* Row = LootTable->FindRow<FLootTableRow>(FName("Row1"), FString(""));
	
	// set min and max from data table
	int MinDrop = Row->MinDropAmount;
	int MaxDrop = Row->MaxDropAmount;
	
	// get random number within range of min and max
	//TODO: Have impact from fortune stat
	int DropAmount = FMath::RandRange(MinDrop, MaxDrop);

	return DropAmount;
}