// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_PlayerController.h"
#include "GameFramework/Character.h"
#include "DeadOfTheKnightTPCharacter.h"
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
	if (ADeadOfTheKnightTPCharacter* DOTK_Character = Cast<ADeadOfTheKnightTPCharacter>(GetCharacter()))
	{
		DOTK_Character->RequestSprintStart();
	}
}

void ADOTK_PlayerController::RequestSprintStop()
{
	if (ADeadOfTheKnightTPCharacter* DOTK_Character = Cast<ADeadOfTheKnightTPCharacter>(GetCharacter()))
	{
		DOTK_Character->RequestSprintStop();
	}
}