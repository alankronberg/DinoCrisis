// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VoxelChunk.h"
#include "BaseDinoCharacter.h"
#include "Vegetation.h"
#include "SaveGameObject.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FChunkSave {
	GENERATED_BODY()
public:
	FChunkSave(){}
	FChunkSave(TArray<int32> chunkData) {
		this->data = chunkData;
	}
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> data;
};

UCLASS()
class DINOCRISIS_API USaveGameObject : public USaveGame
{
	GENERATED_BODY()

public:
	USaveGameObject();
	UPROPERTY(EditAnywhere)
	FVector PlayerLocation;
	UPROPERTY(BlueprintReadWrite)
	TArray<FChunkSave> Chunks;
	FChunkSave chunk;
	UPROPERTY(BlueprintReadWrite)
		TArray<ABaseDinoCharacter*> Dino_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<FString> Dino_Names_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<FTransform> Dino_Location_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<int> Health_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<int> Hunger_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<int> Max_Health_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<int> Max_Hunger_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<bool> Is_Injured_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<float> Slow_Speed_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<float> Normal_Speed_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<AVegetation*> Vegetation_Save;
	UPROPERTY(BlueprintReadWrite)
		TArray<FTransform> Vegetation_Location_Save;
	UPROPERTY(BlueprintReadWrite)
		int Points_Save;
	UPROPERTY(BlueprintReadWrite)
		FTransform Player_Location_Save;
	
};
