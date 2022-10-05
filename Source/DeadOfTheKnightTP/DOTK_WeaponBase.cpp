// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_WeaponBase.h"

// Sets default values
ADOTK_WeaponBase::ADOTK_WeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADOTK_WeaponBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADOTK_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}