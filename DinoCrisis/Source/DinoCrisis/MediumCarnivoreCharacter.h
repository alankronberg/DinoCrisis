// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCarnivoreCharacter.h"
#include "MediumCarnivoreCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API AMediumCarnivoreCharacter : public ABaseCarnivoreCharacter
{
	GENERATED_BODY()
	
	public:
		AMediumCarnivoreCharacter();
	protected:
		void BeginPlay();
};
