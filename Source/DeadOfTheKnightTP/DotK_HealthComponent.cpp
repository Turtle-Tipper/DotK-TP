// Fill out your copyright notice in the Description page of Project Settings.


#include "DotK_HealthComponent.h"

// Sets default values for this component's properties
UDotK_HealthComponent::UDotK_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDotK_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDotK_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDotK_HealthComponent::StartRegenHealth()
{

}

void UDotK_HealthComponent::EndRegenHealth()
{

}

void UDotK_HealthComponent::RequestIncreaseMaxHealth()
{

}