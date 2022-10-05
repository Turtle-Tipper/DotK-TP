// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_ItemBase.h"
#include "DOTK_WeaponBase.generated.h"

UENUM()
enum class EWeaponType : uint8
{
	None			UMETA(DisplayName = "None"),
	Dagger			UMETA(DisplayName = "Dagger"),
	Shield			UMETA(DisplayName = "Shield"),
	Sword			UMETA(DisplayName = "Sword"),
	Axe				UMETA(DisplayName = "Axe"),
	Spear			UMETA(DisplayName = "Spear"),
	Other			UMETA(DisplayName = "Other"),
};

UENUM()
enum class EHandSlot : uint8
{
	None			UMETA(DisplayName = "None"),
	MainHand		UMETA(DisplayName = "Main Hand"),
	OffHand			UMETA(DisplayName = "Off Hand"),
	OneHand			UMETA(DisplayName = "One Hand"),
	TwoHand			UMETA(DisplayName = "Two Hand"),
};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_WeaponBase : public ADOTK_ItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADOTK_WeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Initial attack speed before being modified by stats (agility) or weapon skill/talents. */
	UPROPERTY(EditAnywhere)
	float BaseAttackSpeed = 2.0f;

	/* Initial weapon damage before being modified by stats, weapon skill, crits. */
	UPROPERTY(EditAnywhere)
	float BaseAttackDamage = 5.0f;

	/* Determines the weapon type. For use in choosing attack animation, applying damage modifiers based on weapon skill/talents, and displaying on item info. */
	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;

	/* Determines slot weapon can be equipped in. One Hand can be equipped in either Main Hand or Off Hand. */
	UPROPERTY(EditAnywhere)
	EHandSlot HandSlot;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
