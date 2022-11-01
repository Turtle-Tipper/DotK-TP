// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DotK_CharacterAttributeComponent.h"
#include "DOTK_ItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
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
	Armor			UMETA(DisplayName = "Armor"),
};

UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_ItemBase : public AActor
{
	GENERATED_BODY()

	/* Scene Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootSceneComponent;
		
	/* Static Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemMesh;

	/* 2D Texture Component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTexture2D* ItemImage;
	
public:	
	// Sets default values for this actor's properties
	ADOTK_ItemBase();

	virtual void Use(class ADOTK_PlayerCharacter* Character) PURE_VIRTUAL(UItem, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class ADOTK_PlayerCharacter* Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Custom Overlap begin function
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Custom Overlap end function
	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	/* Level required to use item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelReq;

	/* Weight of item. To be used in encumberance system. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float ItemWeight;

	/* Number of items that can fit into one inventory slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StackSize = 1;

	/* Rarity of item. To be used in determining attribute range. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity ItemRarity;

	/* General type of item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	/* Name of item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	/* Item use text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UseItemText;

	/* Description of item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (Multiline = true))
	FText ItemDescription;

	/* The inventory that owns this item. */
	UPROPERTY()
	class UDOTK_InventoryComponent* OwningInventory;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ** GETTERS ** //
	/** Returns RootSceneComponent **/
	FORCEINLINE class USceneComponent* GetRootSceneComponent() const { return RootSceneComponent; }
	/** Returns StaticMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetStaticMeshComponent() const { return ItemMesh; }
	/* Returns ItemImage. */
	FORCEINLINE class UTexture2D* GetItemImage() const { return ItemImage; }

	FORCEINLINE FString GetItemName() { return ItemName; }

	FORCEINLINE class UDOTK_InventoryComponent* GetOwningInventory() const { return OwningInventory; }

	// ** SETTERS ** //
	void SetOwningInventory(UDOTK_InventoryComponent* Inv) { OwningInventory = Inv; }

	UPROPERTY(Transient)
	class UWorld* World;

};
