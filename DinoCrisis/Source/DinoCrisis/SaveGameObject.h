// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VoxelChunk.h"
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
	
};
