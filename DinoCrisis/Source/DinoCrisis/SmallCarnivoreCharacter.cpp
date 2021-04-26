// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallCarnivoreCharacter.h"

ASmallCarnivoreCharacter::ASmallCarnivoreCharacter()
{
	HerbivoreCollision = CreateDefaultSubobject<UBoxComponent>(FName("Herbivore Collision"));
	HerbivoreCollision->InitBoxExtent(FVector(50, 50, 100));
	HerbivoreCollision->SetupAttachment(RootComponent);
	health = 5;
	maxHealth = 5;
	hunger = 5;
	maxHunger = 5;
	slowSpeed = 400.0f;
	normalSpeed = 800.0f;
	isStarving = false;
	isInjured = false;
}

void ASmallCarnivoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ASmallCarnivoreCharacter::healthAndHungerCycle, 2.0f, true, 5.0f);
	HerbivoreCollision->OnComponentBeginOverlap.AddDynamic(this, &ASmallCarnivoreCharacter::OnOverlapBegin);
}