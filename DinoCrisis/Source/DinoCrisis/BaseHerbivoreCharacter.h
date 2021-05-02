// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDinoCharacter.h"
#include "BaseHerbivoreCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API ABaseHerbivoreCharacter : public ABaseDinoCharacter
{
	GENERATED_BODY()
		
	protected:
		UPROPERTY(EditAnywhere)
		UBoxComponent* VegetationCollision = nullptr;
		UPROPERTY(EditAnywhere)
		UBoxComponent* CarnivoreCollision = nullptr;
};
