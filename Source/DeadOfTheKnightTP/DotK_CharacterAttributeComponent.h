// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DotK_CharacterAttributeComponent.generated.h"

UENUM(BlueprintType)
enum class ECharacterStat : uint8
{
	None			UMETA(DisplayName = "None"),
	Constitution	UMETA(DisplayName = "Constitution"),
	Strength		UMETA(DisplayName = "Strength"),
	Agility			UMETA(DisplayName = "Agility"),
	Intellect		UMETA(DisplayName = "Intellect"),
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDotK_CharacterAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDotK_CharacterAttributeComponent();

	// ** PRIMARY STATS ** //

	/* Armor reduces damage taken. */
	UPROPERTY(EditAnywhere, Category = "Primary Stats")
	int Armor;

	/* Constitution modifies HP and block value. */
	UPROPERTY(EditAnywhere, Category = "Primary Stats")
	int Constitution;

	/* Strength modifies physical damage. */
	UPROPERTY(EditAnywhere, Category = "Primary Stats")
	int Strength;

	/* Agility modifies dodge chance, and critical strike chance. */
	UPROPERTY(EditAnywhere, Category = "Primary Stats")
	int Agility;

	/* Intellect modifies spell damage. */
	UPROPERTY(EditAnywhere, Category = "Primary Stats")
	int Intellect;

	/* Wisdom modifies maximum mana and mana regen. */
	UPROPERTY(EditAnywhere, Category = "Primary Stats")
	int Wisdom;

	// ** SECONDARY STATS ** //

	/* Haste modifies casting speed. */
	UPROPERTY(EditAnywhere, Category = "Secondary Stats")
	float Haste;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// ** STATS FUNCTIONS ** //

	/* Called to permanently increase a stat. On level up or other progression points. */
	void IncreaseStat();

	/* Called to temporarily increase a stat. */
	void BuffStat();

	/* Called to temporarily debuff a stat. */
	void DebuffStat();

	/* Called to update stats. */
	void UpdateStats();
		
};
