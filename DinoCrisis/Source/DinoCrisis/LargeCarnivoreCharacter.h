// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCarnivoreCharacter.h"
#include "LargeCarnivoreCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API ALargeCarnivoreCharacter : public ABaseCarnivoreCharacter
{
	GENERATED_BODY()
	
	public:
		ALargeCarnivoreCharacter();
	protected:
		void BeginPlay();
};
