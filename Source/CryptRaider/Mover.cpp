// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove == true)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
    	FVector TargetLocation = OriginalLocation + MoveOffset;
    	float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;
    	
    	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
    	GetOwner()->SetActorLocation(NewLocation);	
	}
	
	/*
	// Learning about pointers
	AActor* Owner = GetOwner();
	// FString Name = (*Owner).GetActorNameOrLabel();
	// More concise way of above dereferencing:
	FString Name = Owner->GetActorNameOrLabel();

	// Dereferencing
	//UE_LOG(LogTemp, Display, TEXT("Mover Owner: %s"), *Name);

	// Testing Actor Location:
	FVector OwnerLocation = Owner->GetActorLocation();
	FString OwnerLocationString = OwnerLocation.ToCompactString();

	// Combine the two UE_LOGs
	UE_LOG(LogTemp, Display, TEXT("%s location: %s"), *Name, *OwnerLocationString);

	// First pointer location on same actor: 3065465600
	// Second pointer location on same actor: 3833548800
	// When we press play in UE, a whole new set of actors are created.
	// That's why we see new addresses each time we hit play.
	// UE_LOG(LogTemp, Display, TEXT("Mover Owner Address %u"), Owner);

	// Pointing to the same address
	float MyFloat = 5; // Define variable
	float* YourFloat = &MyFloat; // Assign address to pointer
	float FloatValue = *YourFloat; // Get Owner's value from address

	// To get the actual value
	UE_LOG(LogTemp, Display, TEXT("YourFloat Value: %f"), FloatValue);
	// More efficient version of above:
	UE_LOG(LogTemp, Display, TEXT("YourFloat Value: %f"), *YourFloat);

	// This would not work because YourFloat is not a float, but an address:
	// UE_LOG(LogTemp, Display, TEXT("YourFloat Value: %f"), YourFloat);
	*/	
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}


