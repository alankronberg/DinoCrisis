// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseDinoCharacter.h"
#include "Vegetation.h"
#include "VoxelChunkV2.h"
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

	UFUNCTION(BlueprintCallable)
		TArray<int32> getIntsFromString(FString input);

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			TArray<ABaseDinoCharacter*> allDinos;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			TArray<AVegetation*> allVegetation;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			TArray<AVoxelChunkV2*> chunks;
};
