// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_EquipmentBase.h"
#include "DOTK_PlayerCharacter.h"

// Sets default values
ADOTK_EquipmentBase::ADOTK_EquipmentBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComponent = CreateDefaultSubobject<UDotK_CharacterAttributeComponent>(TEXT("AttributeComponent"));

	DurabilityComponent = CreateDefaultSubobject<UDotK_HealthComponent>(TEXT("HealthComponent"));

}

// Called when the game starts or when spawned
void ADOTK_EquipmentBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADOTK_EquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADOTK_EquipmentBase::Use(class ADOTK_PlayerCharacter* Character)
{
	if (Character)
	{
		// Equip

		if (OwningInventory)
		{
			OwningInventory->RemoveFromInventory(this);;
		}
	}
}

void ADOTK_EquipmentBase::RequestTakeDamage(float DamageAmount)
{
	GetDurabilityComponent()->TakeDamage(DamageAmount);
}

void ADOTK_EquipmentBase::RequestHeal(float HealAmount)
{
	GetDurabilityComponent()->Heal(HealAmount);
}

void ADOTK_EquipmentBase::RequestRepair()
{
	GetDurabilityComponent()->Revive(GetDurabilityComponent()->GetMaxHealth());
}