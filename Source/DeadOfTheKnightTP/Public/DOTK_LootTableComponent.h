// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "DeadOfTheKnightTP/DOTK_Itembase.h"
#include "DOTK_LootTableComponent.generated.h"


// Everything accomplished by this struct should be doable with data tables, but this mirrors the TableItem FStruct BP
USTRUCT(BlueprintType)
struct FTableItem
{
	GENERATED_BODY()

	/* Item that will drop. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADOTK_ItemBase* Item;

	/* Percentage chance that above item will drop. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DropChance;

	/* Once an item is determined to have dropped, quantity is determined by range of vars below. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinDropAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxDropAmount;
};


/* Can be created as DefaultSubobject in cpp (in enemy, lootables, etc.), but value should be set in editor for ease of iterations. */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDOTK_LootTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDOTK_LootTableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ADOTK_ItemBase* CalculateDropItem(UDataTable* LootTable);

	int CalculateDropAmount(UDataTable* LootTable);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Loot Datatable set in editor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LootTable)
	UDataTable* LootTable;

	/* Maximum number of items to be "rolled" on. When loot is generated, this is how many times the loot spawning mechanism can be iterated through. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LootTable)
	int MaxNumberOfRolls;
};
