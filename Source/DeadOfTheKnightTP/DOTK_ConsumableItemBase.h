// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_ItemBase.h"
#include "DOTK_ConsumableItemBase.generated.h"

UENUM(BlueprintType)
enum class EConsumableType : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	Food			UMETA(DisplayName = "Food"),
	Drink			UMETA(DisplayName = "Drink"),
	Potion			UMETA(DisplayName = "Potion"),
};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_ConsumableItemBase : public ADOTK_ItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADOTK_ConsumableItemBase();

	virtual void Use(class ADOTK_PlayerCharacter* Character) override;

protected:

	/* Amount of health to be added to character's current health. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthToHeal;
	
	/* Amount of hunger to be added to character's current hunger. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HungerValue;

	/* Amount of saturation to be added to character's current saturation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SaturationValue;

	/* Amount of thirst to be added to character's current thirst. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThirstValue;

	/* The consumable's type. Used to determine sound for using. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EConsumableType ConsumableType;
	
};
