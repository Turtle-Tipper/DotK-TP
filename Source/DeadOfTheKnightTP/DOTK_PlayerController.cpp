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
		InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ADOTK_PlayerController::RequestJump);
		InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ADOTK_PlayerController::RequestStopJump);

		InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ADOTK_PlayerController::RequestSprintStart);
		InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ADOTK_PlayerController::RequestSprintStop);
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