// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTK_ItemBase.h"

// Sets default values
ADOTK_ItemBase::ADOTK_ItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	ItemImage = CreateDefaultSubobject<UTexture2D>(TEXT("ItemImage"));
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
		//if (OtherActor == Cast<ADOTK_PlayerCharacter>(OtherActor))
		//{
		//	//get item name
		//	//create widget
		//}
}

void ADOTK_ItemBase::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//if (OtherActor == Cast<ADOTK_PlayerCharacter>(OtherActor))
	//{
	//	// destroy widget
	//}
}