// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTrigger.h"
#include "Components/BoxComponent.h"
#include "CharacterFrog.h"

// Sets default values
ABaseTrigger::ABaseTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	TriggerType = ETriggerType::None;
}

// Called when the game starts or when spawned
void ABaseTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrigger::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseTrigger::OnOverlapEnd);
}

// Called every frame
void ABaseTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"))

		switch (TriggerType)
		{
		case ETriggerType::Finish:
			if (auto Player = Cast<ACharacterFrog>(OtherActor))
			{
				Player->setGameIsOver(true);
			}
			break;
		}
	}
}

void ABaseTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd"))
	}
}

