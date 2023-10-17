// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "GameFramework/Actor.h"
#include "Misc/TextFilterExpressionEvaluator.h"

UTriggerComponent::UTriggerComponent()
{
	// This is added by default for Actors, but not components? I manually added this
	// to enable ticking and viewing logs for each tick.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	/*
	 *Index-based for loop. Equivalent is used below in range-based.
	for (int32 i = 0; i < Actors.Num(); ++i)
	{
		FString ActorName = Actors[i]->GetActorNameOrLabel();
    	UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *ActorName);
	}
	*/

	// Range-based for loop. Good for collection types that contain things.
	for (AActor* Actor : Actors)
	{
		FString ActorName = Actor->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *ActorName);
	}
}
