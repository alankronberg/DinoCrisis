// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDinoCharacter.h"

// Sets default values
/*
ABaseDinoCharacter::ABaseDinoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DinoCollision = CreateDefaultSubobject<UBoxComponent>(FName("Dino Collision"));
}
*/
// Called when the game starts or when spawned
void ABaseDinoCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ABaseDinoCharacter::healthAndHungerCycle, 2.0f, true, 5.0f);
}

void ABaseDinoCharacter::healthAndHungerCycle()
{
	checkStarvingStatus();
	if (isStarving)
	{
		decrementHealth();
		if (health <= 0)
		{
			Destroy();
		}
		else
		{
			checkInjuryStatus();
			if (isInjured)
			{
				setMovementSpeedSlow();
			}
		}
	}
	else
	{
		decrementHunger();
		incrementHealth();
		checkInjuryStatus();
		if (isInjured)
		{
			setMovementSpeedSlow();
		}
		else
		{
			setMovementSpeedNormal();
		}
	}
}

void ABaseDinoCharacter::decrementHealth()
{
	health--;
}

void ABaseDinoCharacter::incrementHealth()
{
	if (health < maxHealth)
		health++;
}

void ABaseDinoCharacter::decrementHunger()
{
	hunger--;
}

void ABaseDinoCharacter::incrementHunger()
{
	if (hunger < maxHunger)
		hunger++;
}

void ABaseDinoCharacter::setMovementSpeedSlow()
{
	UCharacterMovementComponent* MovementPtr= GetCharacterMovement();
	MovementPtr->MaxWalkSpeed = slowSpeed;
}

void ABaseDinoCharacter::setMovementSpeedNormal()
{
	UCharacterMovementComponent* MovementPtr = GetCharacterMovement();
	MovementPtr->MaxWalkSpeed = normalSpeed;
}

bool ABaseDinoCharacter::checkInjuryStatus()
{
	float injuryThreshold = 0.3 * maxHealth;
	if (health < injuryThreshold) {
		isInjured = true;
	}
	else
	{
		isInjured = false;
	}
	return isInjured;
}

bool ABaseDinoCharacter::checkStarvingStatus()
{
	if (hunger <= 0) {
		isStarving = true;
	}
	else
	{
		isStarving = false;
	}
	return isStarving;
}


