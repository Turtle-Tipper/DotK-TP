// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeadOfTheKnightTPCharacter.h"
#include "DOTK_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_PlayerCharacter : public ADeadOfTheKnightTPCharacter
{
	GENERATED_BODY()
public:

	ADOTK_PlayerCharacter();

protected:

	virtual void Tick(float DeltaTime) override;

protected:

public:
	
};
