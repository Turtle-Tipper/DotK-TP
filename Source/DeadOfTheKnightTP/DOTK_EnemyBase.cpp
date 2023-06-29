// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_EnemyBase.h"

ADOTK_EnemyBase::ADOTK_EnemyBase()
{
	// ** COMPONENT CREATION ** //
	
	// Creates LootTableComponent
	LootTableComponent = CreateDefaultSubobject<UDOTK_LootTableComponent>(TEXT("LootTableComponent"));

}

// Called when the game starts or when spawned
void ADOTK_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADOTK_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADOTK_EnemyBase::OnDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Enemy Killed.")));

	if (LootTableComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Loot table detected.")));

		TArray<FDropItem> DropArray = LootTableComponent->CalculateDrops();

		for (int i = 0; i < DropArray.Num(); i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("In drop array loop;")));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Loot Dropped: %s"),
				*DropArray[i].ItemToDrop.GetDefaultObject()->GetItemName()));
		}
	}
}

void ADOTK_EnemyBase::OnDamageReceived()
{

}