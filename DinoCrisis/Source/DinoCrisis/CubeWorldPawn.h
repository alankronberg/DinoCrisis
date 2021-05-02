// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "SaveGameObject.h"
#include "Engine.h"
#include "VoxelChunk.h"
#include "CubeWorldPawn.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API ACubeWorldPawn : public ADefaultPawn
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int incrementValue;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* incrementActor;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* decrementActor;
private:
	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	//UPROPERTY()
	//AVoxelChunk TheseChunks;

};
