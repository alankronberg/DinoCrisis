// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDinoCharacter.h"
#include "DinoCrisisGameModeBase.h"

// Sets default values

// Called when the game starts or when spawned
void ABaseDinoCharacter::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	gameMode = Cast<ADinoCrisisGameModeBase>(world->GetAuthGameMode());
	if (world)
	{
		if (gameMode)
		{
			gameMode->allDinos.Add(this);
		}
	}
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


