// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "BaseDinoCharacter.generated.h"

UCLASS()
class DINOCRISIS_API ABaseDinoCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void healthAndHungerCycle();
	void decrementHealth();
	void incrementHealth();
	void decrementHunger();
	void incrementHunger();
	void setMovementSpeedSlow();
	void setMovementSpeedNormal();
	bool checkInjuryStatus();
	bool checkStarvingStatus();

protected:
	UPROPERTY(BlueprintReadWrite)
		int health;
	UPROPERTY(BlueprintReadWrite)
		int maxHealth;
	UPROPERTY(BlueprintReadWrite)
		int hunger;
	UPROPERTY(BlueprintReadWrite)
		int maxHunger;
	UPROPERTY(BlueprintReadWrite)
		float slowSpeed;
	UPROPERTY(BlueprintReadWrite)
		float normalSpeed;
	UPROPERTY(BlueprintReadWrite)
		bool isInjured;
	UPROPERTY(BlueprintReadWrite)
		bool isStarving;
	UWorld* world;
	class ADinoCrisisGameModeBase* gameMode;

public:	
	FTimerHandle MemberTimerHandle;

};
