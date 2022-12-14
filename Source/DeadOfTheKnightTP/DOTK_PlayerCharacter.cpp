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

	// Create LineTrace component
	//LineTraceComponent = CreateDefaultSubobject<ULineTraceKismet>(TEXT("LineTraceComponent"));
	//LineTraceComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Create a hunger and thirst component
	HungerThirstComponent = CreateDefaultSubobject<UDOTK_HungerThirstComponent>(TEXT("HungerHealthComponent"));

	// Create a level handler component
	LevelHandlerComponent = CreateDefaultSubobject<UDOTK_LevelHandlerComponent>(TEXT("LevelHandlerComponent"));

	// Create an inventory component
	InventoryComponent = CreateDefaultSubobject<UDOTK_InventoryComponent>(TEXT("InventoryComponent"));

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

	// LineTrace
	LineTrace();
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
	if (InventoryComponent)
	{
		InventoryComponent->OnEncumbranceUpdated.AddDynamic(this, &ADOTK_PlayerCharacter::OnEncumberanceUpdated);
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

// ** TRACE ** //

void ADOTK_PlayerCharacter::LineTrace()
{
	FVector StartPos = GetMesh()->GetSocketLocation("LineTraceStart");
	FVector EndPos = ((GetFollowCamera()->GetForwardVector() * TraceDistance) + StartPos);

	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(this, StartPos, EndPos, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Green, FLinearColor::Yellow, 0.1f);

	if (bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Trace Hit: %s"), *HitResult.GetActor()->GetName()));
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

void ADOTK_PlayerCharacter::IncreaseWeaponSkill(EWeaponType Type)
{
	UE_LOG(LogTemp, Warning, TEXT("IncreaseWeaponSkill called"))
	switch (Type)
	{
		case EWeaponType::Axe:
		{
			// make sure AxeSkill is below max level
			if (AxeSkill.CurrentSkillValue < AxeSkill.MaxSkillValue)
			{
				AxeSkill.CurrentSkillValue += AxeSkill.SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("AXE SKILL INCREASED"))
				
					// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (AxeSkill.CurrentSkillValue > AxeSkill.MaxSkillValue)
				{
					AxeSkill.CurrentSkillValue = AxeSkill.MaxSkillValue;
				}
			}

			break;
		}
		case EWeaponType::Dagger:
		{
			// make sure DaggerSkill is below max level
			if (DaggerSkill.CurrentSkillValue < DaggerSkill.MaxSkillValue)
			{
				DaggerSkill.CurrentSkillValue += DaggerSkill.SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("DAGGER SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (DaggerSkill.CurrentSkillValue > DaggerSkill.MaxSkillValue)
				{
					DaggerSkill.CurrentSkillValue = DaggerSkill.MaxSkillValue;
				}
			}

			break;
		}
		case EWeaponType::Fists:
		{
			// make sure FistSkill is below max level
			if (FistSkill.CurrentSkillValue < FistSkill.MaxSkillValue)
			{
				FistSkill.CurrentSkillValue += FistSkill.SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("FIST SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (FistSkill.CurrentSkillValue > FistSkill.MaxSkillValue)
				{
					FistSkill.CurrentSkillValue = FistSkill.MaxSkillValue;
				}
			}

			break;
		}
		case EWeaponType::Mace:
		{
			// make sure MaceSkill is below max level
			if (MaceSkill.CurrentSkillValue < MaceSkill.MaxSkillValue)
			{
				MaceSkill.CurrentSkillValue += MaceSkill.SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("MACE SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (MaceSkill.CurrentSkillValue > MaceSkill.MaxSkillValue)
				{
					MaceSkill.CurrentSkillValue = MaceSkill.MaxSkillValue;
				}
			}

			break;
		}
		case EWeaponType::Shield:
		{
			// make sure ShieldSkill is below max level
			if (ShieldSkill.CurrentSkillValue < ShieldSkill.MaxSkillValue)
			{
				ShieldSkill.CurrentSkillValue += ShieldSkill.SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("SHIELD SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (ShieldSkill.CurrentSkillValue > ShieldSkill.MaxSkillValue)
				{
					ShieldSkill.CurrentSkillValue = ShieldSkill.MaxSkillValue;
				}
			}

			break;
		}
		case EWeaponType::Spear:
		{
			// make sure SpearSkill is below max level
			if (SpearSkill.CurrentSkillValue < SpearSkill.MaxSkillValue)
			{
				SpearSkill.CurrentSkillValue += SpearSkill.SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("SPEAR SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (SpearSkill.CurrentSkillValue > SpearSkill.MaxSkillValue)
				{
					SpearSkill.CurrentSkillValue = SpearSkill.MaxSkillValue;
				}
			}

			break;
		}
		case EWeaponType::Sword:
		{
			// make sure SwordSkill is below max level
			if (SwordSkill.CurrentSkillValue < SwordSkill.MaxSkillValue)
			{
				SwordSkill.CurrentSkillValue += SwordSkill.SkillUpAmount;
				UE_LOG(LogTemp, Warning, TEXT("SWORD SKILL INCREASED"))
				
				// if it larger, set it max skill level (should only ever happen if level increase isn't whole numbers)
				if (SwordSkill.CurrentSkillValue > SwordSkill.MaxSkillValue)
				{
					SwordSkill.CurrentSkillValue = SwordSkill.MaxSkillValue;
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

void ADOTK_PlayerCharacter::UseItem(ADOTK_ItemBase* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); // BP event
	}
}

void ADOTK_PlayerCharacter::EquipItem(ADOTK_EquipmentBase* Item)
{
	if (Item)
	{
		//GetMesh()->GetSocketByName();
	}
}

void ADOTK_PlayerCharacter::OnEncumberanceUpdated()
{
	if (InventoryComponent->GetIsEncumbered())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is encumbered!"));
		// set lower speed based on encumbrance value
	}
	else
	{
		// currently do nothing
	}
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