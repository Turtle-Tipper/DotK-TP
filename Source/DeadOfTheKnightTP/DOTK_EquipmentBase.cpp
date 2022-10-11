// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_EquipmentBase.h"

// Sets default values
ADOTK_EquipmentBase::ADOTK_EquipmentBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComponent = CreateDefaultSubobject<UDotK_CharacterAttributeComponent>(TEXT("AttributeComponent"));

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