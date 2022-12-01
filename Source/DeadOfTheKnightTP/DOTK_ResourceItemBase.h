// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_ItemBase.h"
#include "DOTK_ResourceItemBase.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	Wood			UMETA(DisplayName = "Wood"),
	Stone			UMETA(DisplayName = "Stone"),
	Metal			UMETA(Displayname = "Metal"),
	Currency		UMETA(DisplayName = "Currency"),
	Animal			UMETA(DisplayName = "Animal"),
};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_ResourceItemBase : public ADOTK_ItemBase
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ADOTK_ResourceItemBase();

protected:

	// Called when the game starts or when spawned
	void BeginPlay() override;

	/* Keeps track of resource type. Can be used to determine interaction sound. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EResourceType ResourceType;
	
};
