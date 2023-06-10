// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeadOfTheKnightTPCharacter.h"
#include "DOTK_LootTableComponent.h"
#include "DOTK_EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_EnemyBase : public ADeadOfTheKnightTPCharacter
{
	GENERATED_BODY()

	/* Loot Table Component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LootTable, meta = (AllowPrivateAccess = "true"))
	UDOTK_LootTableComponent* LootTableComponent;

public:
	ADOTK_EnemyBase();

	// Called every frame.
	virtual void Tick(float DeltaTime) override;




protected:

	virtual void BeginPlay() override;

private:

	
};
