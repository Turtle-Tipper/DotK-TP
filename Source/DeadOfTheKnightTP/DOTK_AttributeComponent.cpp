// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_AttributeComponent.h"

// Sets default values for this component's properties
UDOTK_AttributeComponent::UDOTK_AttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDOTK_AttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDOTK_AttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// ** STATS ** //

void UDOTK_AttributeComponent::IncreaseStat(ECharacterStat StatToIncrease, int IncreaseValue)
{
	if (AvailableSkillPoints > 0)
	{
		switch (StatToIncrease)
		{
		case ECharacterStat::Agility:
		{
			AgilityValue += IncreaseValue;
			break;
		}
		case ECharacterStat::Constitution:
		{
			ConstitutionValue += IncreaseValue;
			break;
		}
		case ECharacterStat::Intellect:
		{
			IntellectValue += IncreaseValue;
			break;
		}
		case ECharacterStat::Strength:
		{
			StrengthValue += IncreaseValue;
			break;
		}
		case ECharacterStat::Wisdom:
		{
			WisdomValue += IncreaseValue;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void UDOTK_AttributeComponent::BuffStat()
{

}

void UDOTK_AttributeComponent::DebuffStat()
{

}