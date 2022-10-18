// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_EquipmentBase.h"
#include "DOTK_WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	None			UMETA(DisplayName = "None"),
	Dagger			UMETA(DisplayName = "Dagger"),
	Shield			UMETA(DisplayName = "Shield"),
	Sword			UMETA(DisplayName = "Sword"),
	Axe				UMETA(DisplayName = "Axe"),
	Mace			UMETA(DisplayName = "Mace"),
	Spear			UMETA(DisplayName = "Spear"),
	Other			UMETA(DisplayName = "Other"),
};

//UENUM(BlueprintType)
//enum class EHandSlot : uint8
//{
//	DEFAULT			UMETA(DisplayName = "DEFAULT"),
//	None			UMETA(DisplayName = "None"),
//	MainHand		UMETA(DisplayName = "Main Hand"),
//	OffHand			UMETA(DisplayName = "Off Hand"),
//	OneHand			UMETA(DisplayName = "One Hand"),
//	TwoHand			UMETA(DisplayName = "Two Hand"),
//};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_WeaponBase : public ADOTK_EquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADOTK_WeaponBase();

	// ** GETTERS ** //

	/* Returns the weapon type. Useful for determining attack animation to play. */
	EWeaponType GetWeaponType() { return WeaponType; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Keeps track of whether damage has been dealt this swing. Set true in BP and false when bHasAttacked is set to false in AnimBP. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasDealtDamage = false;

	/* Initial attack speed before being modified by stats (agility) or weapon skill/talents. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseAttackSpeed = 2.0f;

	/* Initial weapon damage before being modified by stats, weapon skill, crits. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseAttackDamage = 5.0f;

	/* Determines the weapon type. For use in choosing attack animation, applying damage modifiers based on weapon skill/talents, and displaying on item info. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType;

	/* Determines slot weapon can be equipped in. One Hand can be equipped in either Main Hand or Off Hand. */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//EHandSlot HandSlot;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
