// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DOTK_ItemBase.h"
#include "DOTK_InventoryComponent.generated.h"

/* Blueprints will bind to this to update the ui. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDOTK_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDOTK_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddToInventory(ADOTK_ItemBase* Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveFromInventory(ADOTK_ItemBase* Item);

	UFUNCTION(BlueprintCallable)
	void UpdateEncumbrance();

	// ** GETTERS ** //
	int GetSlotLimit() { return SlotLimit; }

	int GetOccupiedSlots() { return OccupiedSlots; }

	int GetItemListSize() { return ItemList.Num(); }

	/* Could be used to control whether or not a text component in inventory widget is displayed. Chests and other containers might not have weight limit. */
	bool HasWeightLimit();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/* Keeps track of whether this inventory has a weight limit. Generally only players and other moveable entities should have a weight limit. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasWeightLimit;

	/* Keeps track of whether the inventory is at / above its weight limit. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEncumbered = false;

	/* Number of inventory slots that the inventory array should be instantiated with. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SlotLimit = 36;
	
	/* Keeps track of the current weight of the inventory. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentWeight;

	/* Weight that can be carried in inventory before being encumbered. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeightLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EncumbranceValue;

	/* Number of inventory slots that will be unusable until being unlocked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LockedSlots;

	/* Number of inventory slots that are already occupied. Should be set based on getting the ItemList size. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int OccupiedSlots;

	/* Number of available inventory slots. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AvailableSlots = SlotLimit - (LockedSlots + OccupiedSlots);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ADOTK_ItemBase*> ItemList;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	//not sure how to make object specific array size
	//ADOTK_ItemBase* ItemList[SlotLimit];

public:
		
};
