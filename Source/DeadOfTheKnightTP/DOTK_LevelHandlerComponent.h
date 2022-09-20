// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DOTK_LevelHandlerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADOFTHEKNIGHTTP_API UDOTK_LevelHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDOTK_LevelHandlerComponent();

	// ** LEVELING ** //

	/* Experience value that must be reached in order to level up. */
	UPROPERTY(EditAnywhere, Category = "Leveling")
		float MaxExperience;

	/* Variable that keeps track of current XP value. */
	UPROPERTY(EditAnywhere, Category = "Leveling")
		float CurrentExperience = 0.0f;

	/* Experience to be rewarded for different activities. */
	UPROPERTY(EditAnywhere, Category = "Leveling")
		float ExperienceIncrease;

	/* Multiplicative value to modify Experience gain. */
	UPROPERTY(EditAnywhere, Category = "Leveling")
		float ExperienceModifier = 1.0f;

	/* Variable that keeps track of current level. */
	UPROPERTY(EditAnywhere, Category = "Leveling")
		int CurrentLevel = 1;

	/* Variable that keeps track of currently available skill points. */
	UPROPERTY(EditAnywhere, Category = "Leveling")
		int AvailableSkillPoints = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ** LEVELING FUNCTIONS ** //
	void IncreaseExperience(float XP, float XPModifier);
	void IncreaseLevel();
	void IncreaseSkillPoints();
};
