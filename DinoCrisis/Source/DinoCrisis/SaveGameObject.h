// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VoxelChunk.h"
#include "SaveGameObject.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API USaveGameObject : public USaveGame
{
	GENERATED_BODY()

public:
	USaveGameObject();
	UPROPERTY(EditAnywhere)
	FVector PlayerLocation;
	//TArray<float> Chunks;
	
};
