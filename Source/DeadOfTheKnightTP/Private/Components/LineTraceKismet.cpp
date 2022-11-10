// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LineTraceKismet.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
ULineTraceKismet::ULineTraceKismet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULineTraceKismet::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULineTraceKismet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LineTrace();
}

void ULineTraceKismet::LineTrace()
{
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = ((GetForwardVector() * TraceDistance) + Start);
	
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Green, FLinearColor::Yellow, 0.1f);

	if (bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Trace Hit: %s"), *HitResult.GetActor()->GetName()));
	}

}


