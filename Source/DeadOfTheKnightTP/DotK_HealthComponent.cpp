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

	if (bCanRegenHealth)
	{
		if (CurrentHP < MaxRegenHP)
		{
			CurrentHP = FMath::FInterpConstantTo(CurrentHP, MaxRegenHP, DeltaTime, HealthRegenAmount);
		}
	}
}

void UDotK_HealthComponent::EnableHealthRegen()
{
	bCanRegenHealth = true;
}

void UDotK_HealthComponent::TakeDamage(float DamageAmount)
{
	if (bIsAlive)
	{
		CurrentHP -= DamageAmount;
		bCanRegenHealth = false;

		// Start timer before character can regen health
		GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle, this, &UDotK_HealthComponent::EnableHealthRegen, HealthRegenDelay, false);
		
		if (CurrentHP <= 0.0f)
		{
			CurrentHP = 0.0f;
			bIsAlive = false;
		}
	}
}

void UDotK_HealthComponent::Heal(float HealAmount)
{
	if (bIsAlive)
	{
		CurrentHP += HealAmount;

		if (CurrentHP > MaxHP)
		{
			CurrentHP = MaxHP;
		}
	}
}

void UDotK_HealthComponent::RequestIncreaseMaxHealth()
{

}