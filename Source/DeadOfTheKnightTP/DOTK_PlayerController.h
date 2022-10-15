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

	void RequestCrouchStart();
	void RequestCrouchStop();

	/* Called for forwards/backward input. */
	void RequestMoveForward(float AxisValue);
	/* Called for side to side input. */
	void RequestMoveRight(float AxisValue);

	/* Called for looking up and down. */
	void RequestLookUp(float AxisValue);
	/* Called for looking left and right. */
	void RequestLookRight(float AxisValue);

	void RequestPickupItem();

	// Base lookup rate, in deg/sec. Other scaling may affect final look up rate
	UPROPERTY(EditAnywhere, Category = "Look")
	float BaseLookUpRate = 90.0f;

	// Base lookright rate, in deg/sec. Other scaling may affect final look right rate
	UPROPERTY(EditAnywhere, Category = "Look")
	float BaseLookRightRate = 90.0f;

	// ** DEBUG ** //
	
	void RequestEat();
	void RequestDrink();
	void RequestEmptyHungerThirst();
};
