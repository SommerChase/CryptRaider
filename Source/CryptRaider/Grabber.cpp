// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Object handled: %s"), *PhysicsHandle->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle Found!"));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UGrabber::Grab()
{
	// Create line coming from camera to debug line tracing:
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan);
	// DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Emerald, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	
	if (bool HasHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			Start,
			End,
			FQuat::Identity, // Means no rotation
			ECC_GameTraceChannel2, // Go to Config/DefaultEngine.ini and search for Grabber to find channel.
			Sphere
		))
		{
		
			DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Emerald, false, 5);
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Blue, false, 5);
			AActor* HitActor = HitResult.GetActor();
			UE_LOG(LogTemp, Display, TEXT("Actor Hit: %s"), *HitActor->GetActorNameOrLabel());
			// FHitResult HitActor = HitResult.GetActor();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("No Actor hit"))
		}
	
	/* Lecture 86:
	// Print rotation of the camera:
	FRotator MyRotation = GetComponentRotation();
	FString RotationString = MyRotation.ToCompactString();
	UE_LOG(LogTemp, Display, TEXT("Grabber Rotation %s"), *RotationString);

	// The 2 lines below were condensed to the 3rd line:
	// UWorld* World = GetWorld();
	// float WorldTimeSeconds = World->TimeSeconds;
	float Time = GetWorld()->TimeSeconds;
	UE_LOG(LogTemp, Display, TEXT("World Seconds: %f"), Time);
	*/
}


void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released"));
}


