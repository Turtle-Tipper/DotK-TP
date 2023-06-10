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