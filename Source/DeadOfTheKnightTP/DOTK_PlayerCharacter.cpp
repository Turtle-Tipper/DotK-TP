// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADOTK_PlayerCharacter::ADOTK_PlayerCharacter()
{
	// ** COMPONENT CREATION ** //

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Create a hunger and thirst component
	HungerThirstComponent = CreateDefaultSubobject<UDOTK_HungerThirstComponent>(TEXT("HungerHealthComponent"));

	// Create a level handler component
	LevelHandlerComponent = CreateDefaultSubobject<UDOTK_LevelHandlerComponent>(TEXT("LevelHandlerComponent"));

}

void ADOTK_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrainStamina(DeltaTime);

	if (GetHungerThirstComponent()->GetIsStarving() == true)
	{
		// if the character is starving, pass in the current HP regen to the starving regen value.
		GetHealthComponent()->RegenerateHealth(DeltaTime, GetHealthComponent()->GetStarvingHealthRegen());
	}
	else if (GetHungerThirstComponent()->GetIsStarving() == false)
	{
		// if the character is not starving, pass in the current HP regen to the max regen value.
		GetHealthComponent()->RegenerateHealth(DeltaTime, GetHealthComponent()->GetMaxHealthRegen());
	}

	GetHungerThirstComponent()->DrainHunger(DeltaTime);
	GetHungerThirstComponent()->DrainThirst(DeltaTime);
}

void ADOTK_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetHealthComponent())
	{
		/* Bind on death delegate. */
		HealthComponent->OnDeathDelegate.AddDynamic(this, &ADOTK_PlayerCharacter::OnDeath);
		/* Bind on damage received delegate. */
		HealthComponent->OnDamageReceivedDelegate.AddDynamic(this, &ADOTK_PlayerCharacter::OnDamageReceived);
	}
}

// ** CHARACTER MOVEMENT ** //

void ADOTK_PlayerCharacter::RequestSprintStart()
{
	if (GetHungerThirstComponent()->GetIsDehydrated() == false)
	{
		if (CurrentStamina > 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = GetSprintSpeed();
			bIsSprinting = true;

			// Stop Stamina regen for a short period
			bCanRegenStamina = false;
			GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTimerHandle);
		}
	}
}

void ADOTK_PlayerCharacter::RequestSprintStop()
{
	if (bIsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = GetWalkSpeed();
		bIsSprinting = false;

		// Start timer to regen stamina when character has stopped sprinting
		GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimerHandle, this, &ADOTK_PlayerCharacter::EnableStaminaRegen, StaminaRegenDelay, false);
	}
}

void ADOTK_PlayerCharacter::RequestJump()
{
		if (GetCharacterMovement()->IsMovingOnGround())
		{
			if (CurrentStamina >= JumpStaminaDrain)
			{
				Jump();
				UseStamina(JumpStaminaDrain);
			}
		}
}

// ** STAMINA ** //

void ADOTK_PlayerCharacter::DrainStamina(float DeltaTime)
{
	if (bIsSprinting)
	{
		CurrentStamina = FMath::FInterpConstantTo(CurrentStamina, 0.0f, DeltaTime, SprintStaminaDrain);

		if (GetHungerThirstComponent()->GetIsDehydrated() == true)
		{
			RequestSprintStop();
		}
		if (CurrentStamina <= 0.0f)
		{
			DepletedAllStamina();
		}
	}
	else
	{
		if (CurrentStamina < MaxStamina)
		{
			if (bCanRegenStamina)
			{
				CurrentStamina = FMath::FInterpConstantTo(CurrentStamina, MaxStamina, DeltaTime, StaminaRegen);
			}
		}
	}
}

void ADOTK_PlayerCharacter::UseStamina(float StaminaToUse)
{
	// use stamina and disable regen
	CurrentStamina -= StaminaToUse;
	bCanRegenStamina = false;
	UE_LOG(LogTemp, Warning, TEXT("Using Stamina"));
	
	// Start timer to regen stamina after using, if not currently sprinting
	if (!bIsSprinting)
	{
		GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimerHandle, this, &ADOTK_PlayerCharacter::EnableStaminaRegen, StaminaRegenDelay, false);
	}
	if (CurrentStamina < 0.0f)
	{
		DepletedAllStamina();
	}
}

void ADOTK_PlayerCharacter::EnableStaminaRegen()
{
	bCanRegenStamina = true;
}

void ADOTK_PlayerCharacter::DepletedAllStamina()
{
	CurrentStamina = 0.0f;
	RequestSprintStop();
	// could also set exhausted state or something?
}

// ** COMBAT ** //

void ADOTK_PlayerCharacter::Attack()
{
	if (!CurrentMainWeapon)
	{
		EWeaponType CurrentWeaponType = EWeaponType::Fists;
	}
	else
	{
		EWeaponType CurrentWeaponType = CurrentMainWeapon->GetWeaponType();
		if (CurrentStamina >= CurrentMainWeapon->GetBaseStaminaDrain())
		{
			if (!bHasAttacked)
			{
				bHasAttacked = true;
				UseStamina(CurrentMainWeapon->GetBaseStaminaDrain());
			}
		}
	}
}

void ADOTK_PlayerCharacter::AlternateAttack()
{

}

void ADOTK_PlayerCharacter::IncreaseWeaponSkill()
{
	EWeaponType CurrentWeaponType = CurrentMainWeapon->GetWeaponType();
	switch (CurrentWeaponType)
	{
		case EWeaponType::Axe:
		{
			// make sure AxeSkill is below max level
			if (AxeSkill < MaxSkillLevel)
			{
				AxeSkill += SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("AXE SKILL INCREASED"))
				
					// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (AxeSkill > MaxSkillLevel)
				{
					AxeSkill = MaxSkillLevel;
				}
			}

			break;
		}
		case EWeaponType::Dagger:
		{
			// make sure DaggerSkill is below max level
			if (DaggerSkill < MaxSkillLevel)
			{
				DaggerSkill += SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("DAGGER SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (DaggerSkill > MaxSkillLevel)
				{
					DaggerSkill = MaxSkillLevel;
				}
			}

			break;
		}
		case EWeaponType::Fists:
		{
			// make sure FistSkill is below max level
			if (FistSkill < MaxSkillLevel)
			{
				FistSkill += SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("FIST SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (FistSkill > MaxSkillLevel)
				{
					FistSkill = MaxSkillLevel;
				}
			}

			break;
		}
		case EWeaponType::Mace:
		{
			// make sure MaceSkill is below max level
			if (MaceSkill < MaxSkillLevel)
			{
				MaceSkill += SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("MACE SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (MaceSkill > MaxSkillLevel)
				{
					MaceSkill = MaxSkillLevel;
				}
			}

			break;
		}
		case EWeaponType::Shield:
		{
			// make sure ShieldSkill is below max level
			if (ShieldSkill < MaxSkillLevel)
			{
				ShieldSkill += SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("SHIELD SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (ShieldSkill > MaxSkillLevel)
				{
					ShieldSkill = MaxSkillLevel;
				}
			}

			break;
		}
		case EWeaponType::Spear:
		{
			// make sure SpearSkill is below max level
			if (SpearSkill < MaxSkillLevel)
			{
				SpearSkill += SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("SPEAR SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (SpearSkill > MaxSkillLevel)
				{
					SpearSkill = MaxSkillLevel;
				}
			}

			break;
		}
		case EWeaponType::Sword:
		{
			// make sure SwordSkill is below max level
			if (SwordSkill < MaxSkillLevel)
			{
				SwordSkill += SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("SWORD SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (SwordSkill > MaxSkillLevel)
				{
					SwordSkill = MaxSkillLevel;
				}
			}

			break;
		}
		default:
		{
			UE_LOG(LogTemp, Warning, TEXT("No weapon type."));
			break;
		}
	}

}

// ** HUNGER AND THIRST ** //

void ADOTK_PlayerCharacter::RequestEat()
{
	GetHungerThirstComponent()->Eat(TestingEatAmount, TestingSaturationAmount);
}

void ADOTK_PlayerCharacter::RequestDrink()
{
	GetHungerThirstComponent()->Drink(TestingDrinkAmount);
}

void ADOTK_PlayerCharacter::RequestEmptyHungerThirst()
{
	GetHungerThirstComponent()->SetCurrentSaturation(0.0f);
	GetHungerThirstComponent()->SetCurrentHunger(0.0f);
	GetHungerThirstComponent()->SetCurrentThirst(0.0f);
}

// ** ITEMS ** //

void ADOTK_PlayerCharacter::PickupItem()
{
	if (bIsOverlappingItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("We picked up an item."))
	}
}

void ADOTK_PlayerCharacter::AddToInventory(ADOTK_ItemBase* Item)
{
	// check to make sure an item is passed in, if not UE_LOG and return
	if (!Item) { UE_LOG(LogTemp, Warning, TEXT("Item to add returning null.")) return; }

	// get inventory struct, get ItemList array and add item to array.
	Inventory.ItemList.Add(Item);
}

// ** HEALTH ** //

void ADOTK_PlayerCharacter::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player is dead."));


	// disable player input on death
	ADOTK_PlayerController* PlayerController = GetController<ADOTK_PlayerController>();
	if (PlayerController)
	{
		PlayerController->DisableInput(PlayerController);
	}
	// could add other logic like death screen, animation, etc
	if (DeathMontage)
	{
		//PlayAnimMontage(DeathMontage, 1, NAME_None);
		// should open DeathScreenWidget here
	}
}

void ADOTK_PlayerCharacter::OnDamageReceived()
{
	UE_LOG(LogTemp, Warning, TEXT("Player took damage."));
}