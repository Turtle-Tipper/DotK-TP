// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_PlayerController.h"
#include "GameFramework/Character.h"
#include "DOTK_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ADOTK_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (InputComponent)
	{
		/* Input bindings for basic movement. Functionality found in PlayerController. */
		InputComponent->BindAxis("Move Forward / Backward", this, &ADOTK_PlayerController::RequestMoveForward);
		InputComponent->BindAxis("Move Right / Left", this, &ADOTK_PlayerController::RequestMoveRight);

		/* Input bindings for looking around. Functionality found in PlayerController. */
		InputComponent->BindAxis("Look Up / Down Mouse", this, &ADOTK_PlayerController::RequestLookUp);
		InputComponent->BindAxis("Turn Right / Left Mouse", this, &ADOTK_PlayerController::RequestLookRight);

		/* Input binding for jumping. Functionality found in PlayerController. */
		InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ADOTK_PlayerController::RequestJump);
		InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ADOTK_PlayerController::RequestStopJump);
		/* Input binding for sprinting. Called in controller, but functionality is still found in DeadOfTheKnightTPCharacter. */
		InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ADOTK_PlayerController::RequestSprintStart);
		InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ADOTK_PlayerController::RequestSprintStop);
		/* Input binding for crouching. Functionality found in PlayerController. */
		InputComponent->BindAction("Crouch", IE_Pressed, this, &ADOTK_PlayerController::RequestCrouchStart);
		InputComponent->BindAction("Crouch", IE_Released, this, &ADOTK_PlayerController::RequestCrouchStop);

		// ** DEBUG ** //
		InputComponent->BindAction("Eat", IE_Pressed, this, &ADOTK_PlayerController::RequestEat);
		InputComponent->BindAction("Drink", IE_Pressed, this, &ADOTK_PlayerController::RequestDrink);
		InputComponent->BindAction("Empty Hunger and Thirst", IE_Pressed, this, &ADOTK_PlayerController::RequestEmptyHungerThirst);
	}
}

void ADOTK_PlayerController::RequestMoveForward(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		// Isolate the Yaw so that looking up/down aren't part of the movement direction calculation.
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, AxisValue);
	}
}

void ADOTK_PlayerController::RequestMoveRight(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		// Isolate the Yaw so that looking up/down aren't part of the movement direction calculation.
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, AxisValue);
	}
}

void ADOTK_PlayerController::RequestLookUp(float AxisValue)
{
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADOTK_PlayerController::RequestLookRight(float AxisValue)
{
	AddYawInput(AxisValue * BaseLookRightRate * GetWorld()->GetDeltaSeconds());
}

void ADOTK_PlayerController::RequestJump()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void ADOTK_PlayerController::RequestStopJump()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void ADOTK_PlayerController::RequestSprintStart()
{
	if (ADOTK_PlayerCharacter* DOTK_PlayerCharacter = Cast<ADOTK_PlayerCharacter>(GetCharacter()))
	{
		DOTK_PlayerCharacter->RequestSprintStart();
	}
}

void ADOTK_PlayerController::RequestSprintStop()
{
	if (ADOTK_PlayerCharacter* DOTK_PlayerCharacter = Cast<ADOTK_PlayerCharacter>(GetCharacter()))
	{
		DOTK_PlayerCharacter->RequestSprintStop();
	}
}

// TO DO: Crouch not fully implemented. No animation graph or animation.

void ADOTK_PlayerController::RequestCrouchStart()
{
	if (GetCharacter())
	{
		GetCharacter()->Crouch();
		GetCharacter()->bIsCrouched = true;
	}
}

void ADOTK_PlayerController::RequestCrouchStop()
{
	if (GetCharacter())
	{
		GetCharacter()->UnCrouch();
		GetCharacter()->bIsCrouched = false;
	}
}

// ** DEBUG ** //

void ADOTK_PlayerController::RequestEat()
{
	if (ADOTK_PlayerCharacter* DOTK_PlayerCharacter = Cast<ADOTK_PlayerCharacter>(GetCharacter()))
	{
		DOTK_PlayerCharacter->RequestEat();
	}
}

void ADOTK_PlayerController::RequestDrink()
{
	if (ADOTK_PlayerCharacter* DOTK_PlayerCharacter = Cast<ADOTK_PlayerCharacter>(GetCharacter()))
	{
		DOTK_PlayerCharacter->RequestDrink();
	}
}

void ADOTK_PlayerController::RequestEmptyHungerThirst()
{
	if (ADOTK_PlayerCharacter* DOTK_PlayerCharacter = Cast<ADOTK_PlayerCharacter>(GetCharacter()))
	{
		DOTK_PlayerCharacter->RequestEmptyHungerThirst();
	}
}