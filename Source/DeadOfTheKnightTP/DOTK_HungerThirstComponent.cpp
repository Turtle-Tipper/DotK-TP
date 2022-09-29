// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_HungerThirstComponent.h"


/* Clamp CurrentHunger between 0 and MaxHunger. */
template<class T>
static T HungerClamp
{
	const T CurrentHunger,
	const T 0.0f,
	const T MaxHunger
};

/* Clamp CurrentSaturation between 0 and MaxSaturation. */ 
template<class T>
static T SaturationClamp
{
	const T CurrentSaturation,
	const T 0.0f,
	const T MaxSaturation
};

/* Clamp CurrentThirst between 0 and MaxThirst. */
template<class T>
static T ThirstClamp
{
	const T CurrentThirst,
	const T 0.0f,
	const T MaxThirst
};

// Sets default values for this component's properties
UDOTK_HungerThirstComponent::UDOTK_HungerThirstComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDOTK_HungerThirstComponent::BeginPlay()
{
	Super::BeginPlay();

	/*
	
	// Clamp CurrentHunger between 0 and MaxHunger
	FMath::Clamp(CurrentHunger, 0.0f, MaxHunger);

	*/
	


	// ...
	
}


// Called every frame
void UDOTK_HungerThirstComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// Hunger Drain logic
	if (!bIsStarving)
	{
		if (CurrentHunger <= 0.0f)
		{
			EnableStarvation();
			return;
		}
		else if (bCanDrainHunger)
		{
			if (CurrentHunger > 0.0f)
			{
				if (CurrentSaturation > 0.0f)
				{
					CurrentSaturation = FMath::FInterpConstantTo(CurrentSaturation, 0.0f, DeltaTime, HungerDrain);
				}
				else if (CurrentSaturation == 0)
				{
					CurrentHunger = FMath::FInterpConstantTo(CurrentHunger, 0.0f, DeltaTime, HungerDrain);
				}
			}
		}
	}


	// Thirst Drain logic
	if (!bIsDehydrated)
	{
		if (CurrentThirst <= 0.0f)
		{
			EnableDehydration();
			return;
		}
		else if (bCanDrainThirst)
		{
			if (CurrentThirst > 0.0f)
			{
				CurrentThirst = FMath::FInterpConstantTo(CurrentThirst, 0.0f, DeltaTime, ThirstDrain);
			}
		}
	}
}

void UDOTK_HungerThirstComponent::Eat(float HungerValue, float SaturationValue)
{
	if (CurrentHunger < MaxHunger)
	{
		CurrentHunger += HungerValue;
		CurrentSaturation += SaturationValue;
		bIsStarving = false;

		bCanDrainHunger = false;
		// Constant timer after eating before hunger can start to drain
		GetWorld()->GetTimerManager().SetTimer(HungerDrainTimerHandle, this, &UDOTK_HungerThirstComponent::EnableHungerDrain, HungerDrainDelay, false);
	}
}

void UDOTK_HungerThirstComponent::Drink(float ThirstValue)
{
	if (CurrentThirst < MaxThirst)
	{
		CurrentThirst += ThirstValue;
		bIsDehydrated = false;
		bCanSprint = true;
		
		bCanDrainThirst = false;
		// Constant timer after drinking before thirst can start to drain
		GetWorld()->GetTimerManager().SetTimer(ThirstDrainTimerHandle, this, &UDOTK_HungerThirstComponent::EnableThirstDrain, ThirstDrainDelay, false);
	}
}

void UDOTK_HungerThirstComponent::EnableHungerDrain()
{
	// Clear HungerDrainDelayTimer
	GetWorld()->GetTimerManager().ClearTimer(HungerDrainTimerHandle);
	bCanDrainHunger = true;
}

void UDOTK_HungerThirstComponent::EnableStarvation()
{
	bIsStarving = true;
	bCanSprint = false;
}

void UDOTK_HungerThirstComponent::EnableThirstDrain()
{
	// Clear ThirstDrainDelayTimer
	GetWorld()->GetTimerManager().ClearTimer(ThirstDrainTimerHandle);
	bCanDrainThirst = true;
}

void UDOTK_HungerThirstComponent::EnableDehydration()
{
	bIsDehydrated = true;
}
