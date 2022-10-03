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
		InputComponent->BindAxis("Move Forward / Backward", this, &ADOTK_PlayerController::RequestMoveForward);
		InputComponent->BindAxis("Move Right / Left", this, &ADOTK_PlayerController::RequestMoveRight);

		/* Input binding for jumping. Functionality found in PlayerController. */
		InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ADOTK_PlayerController::RequestJump);
		InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ADOTK_PlayerController::RequestStopJump);
		/* Input binding for sprinting. Functionality is still found in DeadOfTheKnightTPCharacter. */
		InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ADOTK_PlayerController::RequestSprintStart);
		InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ADOTK_PlayerController::RequestSprintStop);
	}
}

void ADOTK_PlayerController::RequestMoveForward(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		// transform to world space and add it
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), AxisValue);
	}
}

void ADOTK_PlayerController::RequestMoveRight(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		// transform to world space and add it
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), AxisValue);
	}
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