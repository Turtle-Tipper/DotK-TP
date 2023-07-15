// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeadOfTheKnightTPCharacter.h"
#include "DOTK_HungerThirstComponent.h"
#include "DOTK_LevelHandlerComponent.h"
#include "DOTK_InventoryComponent.h"
#include "DOTK_ItemBase.h"
#include "DOTK_PlayerController.h"
//#include "Components/LineTraceKismet.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DOTK_PlayerCharacter.generated.h"

USTRUCT(BlueprintType)
struct FSkill
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentSkillValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSkillValue = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillUpAmount = 1.0f;
};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_PlayerCharacter : public ADeadOfTheKnightTPCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/* Hunger and Thirst Component */
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = HungerAndThirst, meta = (AllowPrivateAccess = "true"))
	class UDOTK_HungerThirstComponent* HungerThirstComponent;

	/* Level Handler Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Level, meta = (AllowPrivateAccess = "true"))
	class UDOTK_LevelHandlerComponent* LevelHandlerComponent;

	/* Inventory Component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UDOTK_InventoryComponent* InventoryComponent;

	/* Line Trace Component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	class ULineTraceKismet* LineTraceComponent;

	/* Instance to set InputMode to UI only. */
	FInputModeUIOnly UIOnly;

public:

	ADOTK_PlayerCharacter();


	// ** ITEMS ** //

	void PickupItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void UseItem(class ADOTK_ItemBase* Item);

	void EquipItem(ADOTK_EquipmentBase* Item);

	// ** HUNGER AND THIRST FUNCTIONS ** //

	UFUNCTION(BlueprintCallable)
	void RequestEat();

	UFUNCTION(BlueprintCallable)
	void RequestDrink();

	UFUNCTION(BlueprintCallable)
	void RequestEmptyHungerThirst();

	// ** MOVEMENT ** //

	UFUNCTION(Server, Reliable)
	virtual void ServerRequestSprintStart();
	virtual void RequestSprintStart() override;

	UFUNCTION(Server, Reliable)
	virtual void ServerRequestSprintStop();
	virtual void RequestSprintStop() override;

	void RequestJump();
	//void RequestJumpStop();

	// ** COMBAT ** //

	virtual void ServerAttack_Implementation() override;
	virtual void Attack() override;

	virtual void ServerAlternateAttack_Implementation() override;
	virtual void AlternateAttack() override;

	UFUNCTION(BlueprintCallable, Category = "Weapon Skills")
	void IncreaseWeaponSkill(EWeaponType Type);

	/* GETTER FUNCTIONS */

	UFUNCTION(BlueprintPure)
	float GetCurrentStaminaPercent() { return CurrentStamina / MaxStamina; }

	float GetMaxStamina() { return MaxStamina; }

	/** Returns HungerThirstComponent subobject **/
	FORCEINLINE class UDOTK_HungerThirstComponent* GetHungerThirstComponent() const { return HungerThirstComponent; }
	/** Returns LevelHandler subobject **/
	FORCEINLINE class UDOTK_LevelHandlerComponent* GetLevelHandler() const { return LevelHandlerComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns LineTrace subobject **/
	FORCEINLINE class ULineTraceKismet* GetLineTrace() const { return LineTraceComponent; }

protected:

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	// ** STAMINA FUNCTIONS ** //

	/* Called to drain stamina. */
	UFUNCTION(BlueprintCallable)
	void DrainStamina(float DeltaTime);

	/* Called to use stamina for single instance. For example, jumping or attacking. */
	UFUNCTION(BlueprintCallable)
	void UseStamina(float StaminaToUse);

	/* Called to rest stamina regen logic. */
	UFUNCTION(BlueprintCallable)
	void EnableStaminaRegen();

	/* Called to perform actions to character once stamina is fully depleted (stun them, have regen delay, etc). */
	UFUNCTION(BlueprintCallable)
	void DepletedAllStamina();

	virtual void OnDeath() override;

	virtual void OnDamageReceived() override;

	/* Called to perform player specific encumbrance logic. For example, lowering movement speed. */
	UFUNCTION(BlueprintCallable)
	void OnEncumberanceUpdated();

	// ** TRACE ** //

	// Creates a line trace from the character's "LineTraceStart" socket (attached to head), and lasting for the length of "TraceDistance". The forward vector
	// is dependent on where the camera is faceing (as opposed to the character itself).
	void LineTrace();

protected:

	/* Tracks whether or not the character is overlapping an item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	bool bIsOverlappingItem;

	// ** TRACE ** //

	/* Determines how far from the trace's start point the trace will end. */
	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceDistance = 500.0f;

	// ** STAMINA ** //

	/* Keeps track of whether character Stamina can currently regen. */
	UPROPERTY(EditAnywhere, Category = "Stamina")
	bool bCanRegenStamina;

	/* The current amount of Stamina the character has. */
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float CurrentStamina = 100.0f;

	/* The highest value a character's Stamina regens to. */
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MaxStamina = 100.0f;

	/* The value of stamina to be drained by sprinting. */
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float SprintStaminaDrain = 5.0f;

	/* The value of stamina used by jumping. */
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float JumpStaminaDrain = 7.0f;

	/* Interval in seconds at which Stamina is drained. */
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float DrainInterval = 1.0f;

	/* The increment at which Stamina is regenerated. */
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaRegen = 8.0f;

	/* Interval in seconds at which Stamina is regenerated. */
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float RegenInterval = 1.0f;

	/* Stamina regen timer handle. */
	FTimerHandle StaminaRegenTimerHandle;

	// ** SPRINT ** //

	/* Value that determines the max speed a player can sprint. */
	UPROPERTY(EditAnywhere, Category = "Character Movement")
	float MaxSprintSpeed = 1500.0f;

	/* The time after using Stamina before it begins to regenerate. */
	UPROPERTY(EditAnywhere, Category = "Character: Stamina")
	float StaminaRegenDelay = 1.5f;

	// ** INVENTORY ** //

	// ** WEAPON SKILLS ** //

	/* Struct for skills that includes a name, current and max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Skills")
	FSkill FistSkill;
	/* Struct for skills that includes a name, current and max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Skills")
	FSkill ShieldSkill;
	/* Struct for skills that includes a name, current and max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Skills")
	FSkill DaggerSkill;
	/* Struct for skills that includes a name, current and max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Skills")
	FSkill SwordSkill;
	/* Struct for skills that includes a name, current and max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Skills")
	FSkill MaceSkill;
	/* Struct for skills that includes a name, current and max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Skills")
	FSkill SpearSkill;
	/* Struct for skills that includes a name, current and max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Skills")
	FSkill AxeSkill;

	/* Character Reference. */

	// ** DEBUG ** //

	/* Hunger amount applied by pressing F. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingEatAmount = 25.0f;

	/* Applied when testing hunger. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingSaturationAmount = 25.0f;

	/* Thirst amount applied by pressing T. For testing purposes. */
	UPROPERTY(EditAnywhere, Category = "Debug")
	float TestingDrinkAmount = 25.0f;

public:
	
};
