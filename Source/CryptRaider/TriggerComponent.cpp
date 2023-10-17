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

	if (GetAcceptableActor() != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *GetAcceptableActor()->GetActorNameOrLabel())
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("None"))
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	// Range-based for loop. Good for collection types that contain things.
	for (AActor* Actor : Actors)
	{
		// FString ActorName = Actor->GetActorNameOrLabel();
		if (Actor->ActorHasTag(AcceptableActorTag))
		{
			return Actor;
		}
	}

	return nullptr;	
}
