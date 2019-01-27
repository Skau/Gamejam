// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCamera.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "math.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"
#include "CharacterFrog.h"

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	SplineComponent->SetupAttachment(RootComponent);

	DistanceFromPlayer = 400;

	GetCameraComponent()->SetFieldOfView(90.f);
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACharacterFrog>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No player found"))
	}
	else
	{
		SetActorLocation(FVector(Player->GetActorLocation().X - DistanceFromPlayer, Player->GetActorLocation().Y, 800));
	}

	GetCameraComponent()->SetWorldRotation(FRotator(-40.f, 0.f, 0.f));

}

void AMainCamera::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	check(Player);

	auto pos = SplineComponent->FindLocationClosestToWorldLocation(Player->GetActorLocation(), ESplineCoordinateSpace::World);

	auto delta = pos.Y - Player->GetActorLocation().Y;
	
	if (delta < -Player->GetMaxYDistance() && Player->GetCanMoveLeft())
	{
		Player->SetCanMoveLeft(false);
	}

	if (delta > Player->GetMaxYDistance() && Player->GetCanMoveRight())
	{
		Player->SetCanMoveRight(false);
	}

	if(delta > -Player->GetMaxYDistance() && !Player->GetCanMoveLeft())
	{
		Player->SetCanMoveLeft(true);
	}

	if (delta < Player->GetMaxYDistance() && !Player->GetCanMoveRight())
	{
		Player->SetCanMoveRight(true);
	}

	// Move camera X axis
	auto CameraLocation = GetCameraComponent()->GetComponentToWorld().GetLocation();
	GetCameraComponent()->AddWorldOffset(FVector((Player->GetActorLocation().X - DistanceFromPlayer) - CameraLocation.X, 0, 0));

	// New Y / Z position for camera	
	auto newPos = SplineComponent->FindLocationClosestToWorldLocation(GetCameraComponent()->GetComponentToWorld().GetLocation(), ESplineCoordinateSpace::World);
	// New rotation for camera
	auto newRotation = SplineComponent->FindDirectionClosestToWorldLocation(GetCameraComponent()->GetComponentToWorld().GetLocation(), ESplineCoordinateSpace::World);

	// Move camera Y / Z axis
	auto oldCameraLocation = GetCameraComponent()->GetComponentToWorld().GetLocation();
	GetCameraComponent()->SetWorldLocation(FVector(oldCameraLocation.X, newPos.Y, newPos.Z));

	// Rotate camera
	GetCameraComponent()->SetWorldRotation(FRotator(-40.f, newRotation.Rotation().Yaw, 0));
}
