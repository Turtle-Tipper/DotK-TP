// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeadOfTheKnightTPGameMode.h"
#include "DeadOfTheKnightTPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADeadOfTheKnightTPGameMode::ADeadOfTheKnightTPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
