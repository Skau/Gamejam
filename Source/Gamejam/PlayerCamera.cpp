// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCamera.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "math.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"
#include "CharacterFrog.h"

APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	SplineComponent->SetupAttachment(RootComponent);

	DistanceFromPlayer = 600;
}

void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	Player =  Cast<ACharacterFrog>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!Player) 
	{
		UE_LOG(LogTemp, Error, TEXT("No player found"))
	}
	else
	{
		SetActorLocation(FVector(Player->GetActorLocation().X - DistanceFromPlayer, Player->GetActorLocation().Y, 300));
	}
}

void APlayerCamera::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (!Player) { return;  }

	// Move camera
	auto CameraLocation = GetCameraComponent()->GetComponentToWorld().GetLocation();
	GetCameraComponent()->SetWorldLocation(FVector(Player->GetActorLocation().X - DistanceFromPlayer, CameraLocation.Y, CameraLocation.Z));

	// Location of start of spline
	auto FirstSplinePointLoc = SplineComponent->GetWorldLocationAtSplinePoint(0);

	// Distance from start of spline to current loc
	auto distance = GetCameraComponent()->GetComponentToWorld().GetLocation().X - SplineComponent->GetWorldLocationAtSplinePoint(0).X;

	// New y position for camera
	auto newPos = SplineComponent->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	// New rotation for camera
	auto newRotation = SplineComponent->GetDirectionAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);

	// Move camera
	auto oldCameraLocation = GetCameraComponent()->GetComponentToWorld().GetLocation();
	GetCameraComponent()->SetWorldLocation(FVector(oldCameraLocation.X, newPos.Y, newPos.Z));

	// Rotate camera
	GetCameraComponent()->SetWorldRotation(FRotator(0, newRotation.Rotation().Yaw, 0));
}
