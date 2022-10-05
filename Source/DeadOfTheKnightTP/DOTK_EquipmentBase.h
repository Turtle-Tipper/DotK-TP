// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_ItemBase.h"
#include "DOTK_EquipmentBase.generated.h"

UENUM()
enum class EEquipSlot : uint8
{

};

UENUM()
enum class EArmorType : uint8
{

};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_EquipmentBase : public ADOTK_ItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's propertiesvv
	ADOTK_EquipmentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
