// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DotK_CharacterAttributeComponent.h"
#include "DOTK_ItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	None			UMETA(DisplayName = "None"),
	Poor			UMETA(DisplayName = "Poor"),
	Common			UMETA(DisplayName = "Common"),
	Uncommon		UMETA(DisplayName = "Uncommon"),
	Rare			UMETA(DisplayName = "Rare"),
	Epic			UMETA(DisplayName = "Epic"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	Resource		UMETA(DisplayName = "Resource"),
	Consumable		UMETA(DisplayName = "Consumable"),
	Weapon			UMETA(DisplayName = "Weapon"),
	Equipment		UMETA(DisplayName = "Equipment"),
};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_ItemBase : public AActor
{
	GENERATED_BODY()

	/* Static Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	/* 2D Texture Component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	class UTexture2D* ItemImage;
	
public:	
	// Sets default values for this actor's properties
	ADOTK_ItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int StackSize = 1;

	UPROPERTY(EditAnywhere)
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ** GETTERS ** //
	/** Returns HungerThirstComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetHungerThirstComponent() const { return StaticMeshComponent; }
	/* Returns ItemImage. */
	FORCEINLINE class UTexture2D* GetItemImage() const { return ItemImage; }

};
