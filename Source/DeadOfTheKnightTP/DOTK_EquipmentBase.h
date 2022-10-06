// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_ItemBase.h"
#include "DOTK_EquipmentBase.generated.h"

UENUM(BlueprintType)
enum class EEquipSlot : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	None			UMETA(DisplayName = "None"),
	Head			UMETA(DisplayName = "Head"),
	Chest			UMETA(DisplayName = "Chest"),
	Legs			UMETA(DisplayName = "Legs"),
	Feet			UMETA(DisplayName = "Feet"),
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	None			UMETA(DisplayName = "None"),
	Cloth			UMETA(DisplayName = "Cloth"),
	Light			UMETA(DisplayName = "Light"),
	Medium			UMETA(DisplayName = "Medium"),
	Heavy			UMETA(DisplayName = "Heavy"),
};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_EquipmentBase : public ADOTK_ItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's propertiesvv
	ADOTK_EquipmentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Determines the equip slot.*/
	UPROPERTY(EditAnywhere)
	EEquipSlot EquipSlot;

	/* Determines the armor type. Different armor types can receive bonuses to them based on talents or armor specialties. */
	UPROPERTY(EditAnywhere)
	EArmorType ArmorType;

	/* Armor applied by piece of gear. Can be improved with attachments. */
	UPROPERTY(EditAnywhere)
	int BaseArmor;

	/* Increases Stamina Drain by this amount per second when equipped. Generally higher the heavier the armor type. Can be changed with attachments and talents. */
	UPROPERTY(EditAnywhere)
	float StaminaDrainModifier = 0.0f;

	/* Decreases Movement Speed by this value when equipped. Generally higher movement speed reduction on heavier armor types. Can be changed with attachments and talents.  */
	UPROPERTY(EditAnywhere)
	float MoveSpeedModifier = 0.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
