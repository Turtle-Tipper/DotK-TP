// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DOTK_ItemBase.h"
#include "DotK_HealthComponent.h"
#include "DOTK_EquipmentBase.generated.h"

UENUM(BlueprintType)
enum class EEquipSlot : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	None			UMETA(DisplayName = "None"),
	Head			UMETA(DisplayName = "Head"),
	Chest			UMETA(DisplayName = "Chest"),
	Legs			UMETA(DisplayName = "Legs"),
	Feet			UMETA(DisplayName = "Feet"),
	MainHand		UMETA(DisplayName = "Main Hand"),
	OffHand			UMETA(DisplayName = "Off Hand"),
	OneHand			UMETA(DisplayName = "One Hand"),
	TwoHand			UMETA(DisplayName = "Two Hand"),
};


UCLASS()
class DEADOFTHEKNIGHTTP_API ADOTK_EquipmentBase : public ADOTK_ItemBase
{
	GENERATED_BODY()

	/* Attribute Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	class UDotK_CharacterAttributeComponent* AttributeComponent;

	/*Health Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Durability, meta = (AllowPrivateAccess = "true"))
	class UDotK_HealthComponent* DurabilityComponent;

public:
	// Sets default values for this actor's properties
	ADOTK_EquipmentBase();
	
	/* Called to apply durability damage to equipment. */
	void RequestTakeDamage(float Damage);

	/* Called to increase remaining durability on equipment. */
	void RequestHeal(float Heal);

	/* Called to fully repair equipment (at workbench etc). */
	void RequestRepair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Determines the equip slot.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipSlot EquipSlot;

	/* Increases Stamina Drain by this amount per second when equipped. Generally higher the heavier the armor type. Can be changed with attachments and talents. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaDrainModifier = 0.0f;

	/* Decreases Movement Speed by this value when equipped. Generally higher movement speed reduction on heavier armor types. Can be changed with attachments and talents.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeedModifier = 0.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Attribute subobject **/
	FORCEINLINE class UDotK_CharacterAttributeComponent* GetAttributeComponent() const { return AttributeComponent; }

	/** Returns Health subobject **/
	FORCEINLINE class UDotK_HealthComponent* GetDurabilityComponent() const { return DurabilityComponent; }

};
