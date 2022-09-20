// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DotK_CharacterAttributeComponent.h"
#include "DOTK_LevelHandlerComponent.h"
#include "DotK_HealthComponent.h"
#include "DotK_DamageHandlerComponent.h"
#include "DeadOfTheKnightTPCharacter.generated.h"



UCLASS(config=Game)
class ADeadOfTheKnightTPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/* Health Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	class UDotK_HealthComponent* HealthComponent;

	/* Damage Manager Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	class UDotK_DamageHandlerComponent* DamageHandlerComponent;

	/* Attribute Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	class UDotK_CharacterAttributeComponent* AttributeComponent;

	/* Level Handler Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Level, meta = (AllowPrivateAccess = "true"))
	class UDOTK_LevelHandlerComponent* LevelHandlerComponent;

public:
	ADeadOfTheKnightTPCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	// ** SPRINT ** //

	bool bIsSprinting = false;

	/* Additive value that can be used to modify sprint speed.*/
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float SprintModifier = 0.0f;

	/* Additive value to base movement speed. */
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float SprintSpeed = 200.0f;

	/* Value that determines the max speed a player can sprint. */
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float MaxSprintSpeed = 1500.0f;

	// ** STAMINA ** //
	
	/* The current amount of Stamina the character has. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float Stamina = 100.0f;

	/* The increment at which Stamina is drained. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaDrain = 5.0f;

	/* Multiplicative value that can be used to modify Stamina drain.*/
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaDrainModifier;

	/* The increment at which Stamina is regenerated. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaRegen = 8.0f;

	/* The lowest a players Stamina will drain to. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float MinStamina = 0.0f;

	/* Additive value that modifies the max Stamina a character can have. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float MaxStaminaModifier = 0.0f;

	/* The highest value a character's Stamina regens to. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float MaxStamina = 100.0f + MaxStaminaModifier;

	/*
		Management of types of Stamina drain might be better with Data Table than with an ENUM.
	*/

protected:

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// ** CHARACTER MOVEMENT FUNCTIONS ** //
	void RequestSprintStart();
	void RequestSprintStop();
	//bool CanSprint(float Speed);
	void RequestCrouchStart();
	void RequestCrouchStop();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	// ** STAMINA FUNCTIONS ** //
	float DrainStamina(float StaminaDrainModifier);
	float RegenStamina(float StaminaRegenModifier);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	float GetSprintSpeed();
};

