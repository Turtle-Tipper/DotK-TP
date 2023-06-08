// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "DeadOfTheKnightTP/DOTK_Itembase.h"
#include "DOTK_LootTableComponent.generated.h"

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


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDOTK_LootTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDOTK_LootTableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UDataTable*> TableItems;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
