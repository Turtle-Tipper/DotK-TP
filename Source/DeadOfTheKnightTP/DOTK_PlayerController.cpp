// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ADOTK_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (InputComponent)
	{
		InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ADOTK_PlayerController::RequestJump);
		InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ADOTK_PlayerController::RequestStopJump);
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