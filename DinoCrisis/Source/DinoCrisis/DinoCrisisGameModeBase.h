// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseDinoCharacter.h"
#include "Vegetation.h"
#include "GameFramework/GameModeBase.h"
#include "DinoCrisisGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API ADinoCrisisGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	FString getMapDataFromFile();

	UFUNCTION(BlueprintCallable)
		void logMessage(FString message);

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			TArray<ABaseDinoCharacter*> allDinos;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			TArray<AVegetation*> allVegetation;

};
