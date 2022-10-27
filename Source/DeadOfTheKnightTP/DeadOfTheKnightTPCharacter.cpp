// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeadOfTheKnightTPCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

//////////////////////////////////////////////////////////////////////////
// ADeadOfTheKnightTPCharacter

ADeadOfTheKnightTPCharacter::ADeadOfTheKnightTPCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// ** COMPONENT CREATION ** //

	// Create a health component
	HealthComponent = CreateDefaultSubobject<UDotK_HealthComponent>(TEXT("HealthComponent"));

	// Create a damage handler component
	DamageHandlerComponent = CreateDefaultSubobject<UDotK_DamageHandlerComponent>(TEXT("DamageHandlerComponent"));
												   
	// Create an attribute component
	CharacterAttributeComponent = CreateDefaultSubobject<UDotK_CharacterAttributeComponent>(TEXT("CharacterAttributeComponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADeadOfTheKnightTPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ADeadOfTheKnightTPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ADeadOfTheKnightTPCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADeadOfTheKnightTPCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADeadOfTheKnightTPCharacter::TouchStopped);

	// ** DEBUG ** //

	PlayerInputComponent->BindAction("Take Damage", IE_Pressed, this, &ADeadOfTheKnightTPCharacter::RequestTakeDamage);
	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &ADeadOfTheKnightTPCharacter::RequestHeal);
}


void ADeadOfTheKnightTPCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ADeadOfTheKnightTPCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ADeadOfTheKnightTPCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ADeadOfTheKnightTPCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

// ** CHARACTER MOVEMENT ** //

void ADeadOfTheKnightTPCharacter::RequestSprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = GetSprintSpeed();
	bIsSprinting = true;
}

void ADeadOfTheKnightTPCharacter::RequestSprintStop()
{
	if (bIsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = GetWalkSpeed();
		bIsSprinting = false;
	}
}

// ** HEALTH ** //

void ADeadOfTheKnightTPCharacter::RequestTakeDamage()
{
	GetHealthComponent()->TakeDamage(TestingDamageAmount);
}

void ADeadOfTheKnightTPCharacter::RequestHeal()
{
	GetHealthComponent()->Heal(TestingHealAmount);
}

// ** COMBAT ** //
void ADeadOfTheKnightTPCharacter::Attack()
{
	if (!CurrentMainWeapon)
	{
		EWeaponType CurrentWeaponType = EWeaponType::Fists;
	}
	else
	{
		EWeaponType CurrentWeaponType = CurrentMainWeapon->GetWeaponType();
		bHasAttacked = true;
	}
}

void ADeadOfTheKnightTPCharacter::AlternateAttack()
{
	if (!CurrentMainWeapon)
	{
		EWeaponType CurrentWeaponType = EWeaponType::Fists;
	}
	else
	{
		EWeaponType CurrentWeaponType = CurrentOffWeapon->GetWeaponType();
	}
}

//Called every frame.
void ADeadOfTheKnightTPCharacter::Tick(float DeltaTime)
{

}