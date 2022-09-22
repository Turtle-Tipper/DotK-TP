// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DotK_CharacterAttributeComponent.h"
#include "DOTK_LevelHandlerComponent.h"
#include "DotK_HealthComponent.h"
#include "DotK_DamageHandlerComponent.h"
#include "Math/UnrealMathUtility.h"
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

	/* Damage Handler Component */
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

	/* Walking movement speed. */
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float WalkSpeed = 450.0f;

	/* Sprint movement speed. */
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float SprintSpeed = 650.0f;

	/* Value that determines the max speed a player can sprint. */
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float MaxSprintSpeed = 1500.0f;

	// ** STAMINA ** //
	
	/* The current amount of Stamina the character has. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float Stamina = 100.0f;

	/* The value of stamina to be drained. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaDrain = 5.0f;

	/* Interval in seconds at which Stamina is drained. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float DrainInterval = 1.0f;

	/* Multiplicative value that can be used to modify Stamina drain.*/
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaDrainModifier;

	/* The increment at which Stamina is regenerated. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaRegen = 8.0f;

	/* Interval in seconds at which Stamina is regenerated. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float RegenInterval = 1.0f;

	/* Additive value that modifies the max Stamina a character can have. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float MaxStaminaModifier = 0.0f;

	/* The highest value a character's Stamina regens to. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float MaxStamina = 100.0f + MaxStaminaModifier;

	/* Damage amount applied by pressing K. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingDamageAmount = 5.0f;

	/* Heal amount applied by pressing H. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingHealAmount = 5.0f;

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
	
	/* Called to drain stamina. */
	UFUNCTION(BlueprintCallable)
	void DrainStamina(float DrainModifier);
	
	/* Called to start regenerating stamina. */
	UFUNCTION(BlueprintCallable)
	void RegenStaminaStart();

	/* Called to stop regenerating stamina. */
	UFUNCTION(BlueprintCallable)
	void RegenStaminaStop(float MaxStam, float CurrentStam);

	UFUNCTION(BlueprintCallable)
	void RequestTakeDamage();

	UFUNCTION(BlueprintCallable)
	void RequestHeal();
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

	// ** GETTER FUNCTIONS ** //

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns HealthComponent subobject **/
	FORCEINLINE class UDotK_HealthComponent* GetHealthComponent() const { return HealthComponent; }
	/** Returns DamageHandler subobject **/
	FORCEINLINE class UDotK_DamageHandlerComponent* GetDamageHandler() const { return DamageHandlerComponent; }
	/** Returns Attribute subobject **/
	FORCEINLINE class UDotK_CharacterAttributeComponent* GetAttributeComponent() const { return AttributeComponent; }
	/** Returns LevelHandler subobject **/
	FORCEINLINE class UDOTK_LevelHandlerComponent* GetLevelHandler() const { return LevelHandlerComponent; }
	
	float GetSprintSpeed() { return SprintSpeed; }

	float GetWalkSpeed() { return WalkSpeed; }

	float GetMaxStamina() { return MaxStamina; }
};

