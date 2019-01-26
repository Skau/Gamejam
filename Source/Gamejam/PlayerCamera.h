// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "PlayerCamera.generated.h"

class ACharacterFrog;
class ACameraSpline;
class USplineComponent;

UCLASS()
class GAMEJAM_API APlayerCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	APlayerCamera();

	void BeginPlay() override;

	void Tick(float deltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacterFrog* Player;

	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceFromPlayer;
};
