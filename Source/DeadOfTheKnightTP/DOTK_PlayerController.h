// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DOTK_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
protected:

	void SetupInputComponent() override;

	void RequestJump();
	void RequestStopJump();

	void RequestSprintStart();
	void RequestSprintStop();

	/** Called for forwards/backward input */
	void RequestMoveForward(float AxisValue);
	/** Called for side to side input */
	void RequestMoveRight(float AxisValue);
};
