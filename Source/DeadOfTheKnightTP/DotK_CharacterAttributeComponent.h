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
	Wisdom			UMETA(DisplayName = "Wisdom"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDotK_CharacterAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDotK_CharacterAttributeComponent();

	// ** STATS FUNCTIONS ** //

	/* Called to permanently increase a stat. On level up or other progression points. */
	UFUNCTION(BlueprintCallable)
	void IncreaseStat(ECharacterStat StatToIncrease, int IncreaseValue);

	/* Called to temporarily increase a stat. */
	UFUNCTION(BlueprintCallable)
	void BuffStat();

	/* Called to temporarily debuff a stat. */
	UFUNCTION(BlueprintCallable)
	void DebuffStat();

	/* GETTER FUNCTIONS */

	UFUNCTION(BlueprintPure)
	int GetAvailableSkillPoints() { return AvailableSkillPoints; }

	/* STATS */

	UFUNCTION(BlueprintPure)
	int GetConstitutionValue() { return ConstitutionValue; }
	UFUNCTION(BlueprintPure)
	int GetStrengthValue() { return StrengthValue; }
	UFUNCTION(BlueprintPure)
	int GetAgilityValue() { return AgilityValue; }
	UFUNCTION(BlueprintPure)
	int GetIntellectValue() { return IntellectValue; }
	UFUNCTION(BlueprintPure)
	int GetWisdomValue() { return WisdomValue; }
	UFUNCTION(BlueprintPure)
	int GetHasteValue() { return HasteValue; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/* Variable that keeps track of currently available skill points. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	int AvailableSkillPoints = 1;

	// ** PRIMARY STATS ** //

	//EPrimaryStat PrimaryStats;

	TArray<uint8> PrimaryStatArray;

	/* Armor reduces damage taken. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Stats")
	int ArmorValue;

	/* Constitution modifies HP and block value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Stats")
	int ConstitutionValue;

	/* Strength modifies physical damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Stats")
	int StrengthValue;

	/* Agility modifies attack speed and critical strike chance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Stats")
	int AgilityValue;

	/* Intellect modifies spell damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Stats")
	int IntellectValue;

	/* Wisdom modifies maximum mana and mana regen. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Stats")
	int WisdomValue;

	// ** SECONDARY STATS ** //

	/* Haste modifies casting speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Stats")
	float HasteValue;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
