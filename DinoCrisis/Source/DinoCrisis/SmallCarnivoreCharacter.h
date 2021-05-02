// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCarnivoreCharacter.h"
#include "SmallCarnivoreCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API ASmallCarnivoreCharacter : public ABaseCarnivoreCharacter
{
	GENERATED_BODY()

	public:
		ASmallCarnivoreCharacter();
	protected:
		void BeginPlay();
};
