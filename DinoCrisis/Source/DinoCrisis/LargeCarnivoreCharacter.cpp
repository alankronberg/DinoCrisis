// Fill out your copyright notice in the Description page of Project Settings.


#include "LargeCarnivoreCharacter.h"

ALargeCarnivoreCharacter::ALargeCarnivoreCharacter()
{
	HerbivoreCollision = CreateDefaultSubobject<UBoxComponent>(FName("Herbivore Collision"));
	HerbivoreCollision->InitBoxExtent(FVector(50, 50, 100));
	HerbivoreCollision->SetupAttachment(RootComponent);
	health = 20;
	maxHealth = 20;
	hunger = 20;
	maxHunger = 20;
	slowSpeed = 200.0f;
	normalSpeed = 1000.0f;
	isStarving = false;
	isInjured = false;
}

void ALargeCarnivoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ALargeCarnivoreCharacter::healthAndHungerCycle, 2.0f, true, 5.0f);
	HerbivoreCollision->OnComponentBeginOverlap.AddDynamic(this, &ALargeCarnivoreCharacter::OnOverlapBegin);
}