// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterFrog.generated.h"

UCLASS()
class GAMEJAM_API ACharacterFrog : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterFrog();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetMaxYDistance() { return MaxYDistance; }

	bool GetCanMoveRight() { return bCantMoveRight; }
	bool GetCanMoveLeft() { return bCantMoveLeft;  }

	void SetCanMoveRight(bool Value) { bCantMoveRight = Value; }
	void SetCanMoveLeft(bool Value) { bCantMoveLeft = Value; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxYDistance;

	UPROPERTY(EditAnywhere)
	bool bCantMoveRight;
	UPROPERTY(EditAnywhere)
	bool bCantMoveLeft;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

private:
	void Jump();

	void HighJump();
};
