// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_ItemBase.h"
#include "DOTK_WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_WeaponBase : public ADOTK_ItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADOTK_WeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
