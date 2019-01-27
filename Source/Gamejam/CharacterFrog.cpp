// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterFrog.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"




// Sets default values
ACharacterFrog::ACharacterFrog()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	MaxYDistance = 800.f;
}

// Called when the game starts or when spawned
void ACharacterFrog::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(0));
}

// Called every frame
void ACharacterFrog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterFrog::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterFrog::Jump);
	PlayerInputComponent->BindAction("HighJump", IE_Pressed, this, &ACharacterFrog::HighJump);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterFrog::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterFrog::MoveRight);
}

void ACharacterFrog::Jump()
{
	if (!GetCharacterMovement()->IsFalling())
		LaunchCharacter((GetActorUpVector() * 500) + (GetActorForwardVector() * 1000), false, false);
}

void ACharacterFrog::HighJump()
{
	if (!GetCharacterMovement()->IsFalling())
		LaunchCharacter((GetActorUpVector() * 800), false, false);
}

void ACharacterFrog::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACharacterFrog::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (Value < 0 && bCantMoveRight || Value > 0 && bCantMoveLeft)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(Direction, Value);
		}
	}
}


