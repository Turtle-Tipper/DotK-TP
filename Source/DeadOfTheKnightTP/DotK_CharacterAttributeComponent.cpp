// Fill out your copyright notice in the Description page of Project Settings.


#include "DotK_CharacterAttributeComponent.h"

// Sets default values for this component's properties
UDotK_CharacterAttributeComponent::UDotK_CharacterAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDotK_CharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDotK_CharacterAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// ** STATS ** //

void UDotK_CharacterAttributeComponent::UpdateStats(int NewStatValue)
{

}

void UDotK_CharacterAttributeComponent::IncreaseStat(ECharacterStat StatToIncrease, int IncreaseValue)
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

void UDotK_CharacterAttributeComponent::BuffStat()
{

}

void UDotK_CharacterAttributeComponent::DebuffStat()
{

}

int UDotK_CharacterAttributeComponent::GetStatValue(ECharacterStat StatToRetrieve)
{
	switch (StatToRetrieve)
	{
	case ECharacterStat::Agility:
	{
		return AgilityValue;
	}
	case ECharacterStat::Constitution:
	{
		return ConstitutionValue;
	}
	case ECharacterStat::Intellect:
	{
		return IntellectValue;
	}
	case ECharacterStat::Strength:
	{
		return StrengthValue;
	}
	case ECharacterStat::Wisdom:
	{
		return WisdomValue;
	}
	default:
	{
		return NULL;
	}
	}
}