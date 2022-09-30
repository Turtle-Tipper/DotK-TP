// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_LevelHandlerComponent.h"

// Sets default values for this component's properties
UDOTK_LevelHandlerComponent::UDOTK_LevelHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDOTK_LevelHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDOTK_LevelHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// ** LEVELING ** //

void UDOTK_LevelHandlerComponent::IncreaseExperience(float XP, float XPModifier)
{

}

void UDOTK_LevelHandlerComponent::IncreaseLevel()
{

}

void UDOTK_LevelHandlerComponent::IncreaseSkillPoints()
{

}