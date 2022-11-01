// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_ItemBase.h"
#include "DOTK_ConsumableItemBase.generated.h"

/**
 * 
 */
UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_ConsumableItemBase : public ADOTK_ItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADOTK_ConsumableItemBase();

	virtual void Use(class ADOTK_PlayerCharacter* Character) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthToHeal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HungerValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SaturationValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThirstValue;
	
};
