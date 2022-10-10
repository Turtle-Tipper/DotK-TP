// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_EquipmentBase.h"
#include "DOTK_ArmorBase.generated.h"

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
class DEADOFTHEKNIGHTTP_API ADOTK_ArmorBase : public ADOTK_EquipmentBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ADOTK_ArmorBase();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Armor applied by piece of gear. Can be improved with attachments. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BaseArmor;

	/* Determines the armor type. Different armor types can receive bonuses to them based on talents or armor specialties. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EArmorType ArmorType;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
