// Fill out your copyright notice in the Description page of Project Settings.


#include "MediumCarnivoreCharacter.h"

AMediumCarnivoreCharacter::AMediumCarnivoreCharacter()
{
	HerbivoreCollision = CreateDefaultSubobject<UBoxComponent>(FName("Herbivore Collision"));
	HerbivoreCollision->InitBoxExtent(FVector(50, 50, 100));
	HerbivoreCollision->SetupAttachment(RootComponent);
	health = 10;
	maxHealth = 10;
	hunger = 10;
	maxHunger = 10;
	slowSpeed = 300.0f;
	normalSpeed = 700.0f;
	isStarving = false;
	isInjured = false;
}

void AMediumCarnivoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMediumCarnivoreCharacter::healthAndHungerCycle, 2.0f, true, 5.0f);
	HerbivoreCollision->OnComponentBeginOverlap.AddDynamic(this, &AMediumCarnivoreCharacter::OnOverlapBegin);
}