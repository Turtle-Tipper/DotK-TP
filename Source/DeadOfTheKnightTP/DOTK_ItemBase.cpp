// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_ItemBase.h"

// Sets default values
ADOTK_ItemBase::ADOTK_ItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	ItemImage = CreateDefaultSubobject<UTexture2D>(TEXT("ItemImage"));

	OnActorBeginOverlap.AddDynamic(this, &ADOTK_ItemBase::OnBeginOverlap);

	OnActorEndOverlap.AddDynamic(this, &ADOTK_ItemBase::OnEndOverlap);
}

// Called when the game starts or when spawned
void ADOTK_ItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADOTK_ItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADOTK_ItemBase::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == Cast<ADOTK_PlayerCharacter>(OtherActor))
	{
		if (!GameWidgetClass) { UE_LOG(LogTemp, Warning, TEXT("No Game Widget Class detected.")) return; }

		//set item name
		SetCorrectItemName(ItemName);

		// get player controller to add to
		PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		GameWidget = CreateWidget<UDOTK_GameWidget>(PC, GameWidgetClass);
		//create widget

		if (!GameWidget) { UE_LOG(LogTemp, Warning, TEXT("Game Widget returning null.")) return; }

		GameWidget->AddToViewport();
	}
}

void ADOTK_ItemBase::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == Cast<ADOTK_PlayerCharacter>(OtherActor))
	{
		// destroy widget
		if (!GameWidget) { UE_LOG(LogTemp, Warning, TEXT("Game Widget returning null.")) return; }

		GameWidget->RemoveFromParent();
	}
}