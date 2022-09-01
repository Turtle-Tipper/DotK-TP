// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
public:
	ADeadOfTheKnightTPCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	/* Value that can be fed into a SprintSpeed function to modify SprintSpeed based on progression*/
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float SprintModifier;

	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float SprintSpeed;

	/* Value that can be used to clamp max speed. */
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float MaxSprintSpeed;

	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float StaminaModifier = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float MinStamina = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float MaxStamina = 100.0f + StaminaModifier;

	bool bIsSprinting = false;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

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

	/* Sprint
	*/

	void RequestSprintStart();
	void RequestSprintStop();

	void RequestCrouchStart();
	void RequestCrouchStop();

	void DrainStamina();
	void RegenStamina();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

