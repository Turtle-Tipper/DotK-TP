// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DotK_CharacterAttributeComponent.h"
#include "DotK_HealthComponent.h"
#include "DotK_DamageHandlerComponent.h"
#include "DOTK_WeaponBase.h"
#include "Math/UnrealMathUtility.h"
#include "DeadOfTheKnightTPCharacter.generated.h"

UCLASS(config=Game)
// ADeadOfTheKnightTPCharacter
class ADeadOfTheKnightTPCharacter : public ACharacter
{
	GENERATED_BODY()

	/* Damage Handler Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	class UDotK_DamageHandlerComponent* DamageHandlerComponent;

	/* Attribute Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	class UDotK_CharacterAttributeComponent* CharacterAttributeComponent;

public:
	ADeadOfTheKnightTPCharacter();

	/* Called to attack. */
	virtual void Attack();

	/* Called to perform alternate attack. Could be swing with off-hand weapon or block with shield/two-hand weapon. */
	virtual void AlternateAttack();


	// ** CHARACTER MOVEMENT FUNCTIONS ** //
	virtual void RequestSprintStart();
	virtual void RequestSprintStop();

	// ** GETTER FUNCTIONS ** //

	/** Returns HealthComponent subobject **/
	FORCEINLINE class UDotK_HealthComponent* GetHealthComponent() const { return HealthComponent; }
	/** Returns DamageHandler subobject **/
	FORCEINLINE class UDotK_DamageHandlerComponent* GetDamageHandler() const { return DamageHandlerComponent; }
	/** Returns Attribute subobject **/
	FORCEINLINE class UDotK_CharacterAttributeComponent* GetCharacterAttributeComponent() const { return CharacterAttributeComponent; }

	float GetSprintSpeed() { return SprintSpeed; }

	float GetWalkSpeed() { return WalkSpeed; }

	bool GetIsCrouched() { return bIsCrouched; }

	// ** SETTERS ** //

	void SetWalkSpeed(float Speed) { WalkSpeed = Speed; }

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:

	// Called every frame.
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

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

	// ** DEBUG ** //
	
	UFUNCTION(BlueprintCallable)
	void RequestTakeDamage();

	UFUNCTION(BlueprintCallable)
	void RequestHeal();

	// TODO: implementation
	virtual void OnDeath();

	// TODO:: implementation
	virtual void OnDamageReceived();

	/* The weapon the character is currently using in their main hand. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	ADOTK_WeaponBase* CurrentMainWeapon;

	/* The weapon the character is currently using in their off hand. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	ADOTK_WeaponBase* CurrentOffWeapon;

	/* Reference to death animation montage. ReadWrite as it may be useful for setting up a struct to randomly select from. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DeathMontage;

	/* Keeps track of whether or not the character is sprinting. */
	UPROPERTY(EditAnywhere, Category = "Character Movement")
	bool bIsSprinting = false;

	/* Keeps track of whether or not the character has attacked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bHasAttacked = false;

	/* Additive value that can be used to modify sprint speed.*/
	UPROPERTY(EditAnywhere, Category = "Character Movement")
	float SprintModifier = 0.0f;

	/* Walking movement speed. */
	UPROPERTY(EditAnywhere, Category = "Character Movement")
	float WalkSpeed = 450.0f;

	/* Sprint movement speed. */
	UPROPERTY(EditAnywhere, Category = "Character Movement")
	float SprintSpeed = 650.0f;

	//Damage and Health

	/* Damage amount applied by pressing K. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingDamageAmount = 5.0f;

	/* Heal amount applied by pressing H. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingHealAmount = 5.0f;

	/* Base attack speed of a character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseAttackSpeed = 1.0f;

	/* Health Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	class UDotK_HealthComponent* HealthComponent;
	
protected:

public:


};

