// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelCube.h"
#include "VoxelChunk.generated.h"

UCLASS()
class DINOCRISIS_API AVoxelChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelChunk();

	UProceduralMeshComponent* PMC;

	TArray<AVoxelCube*> cubes;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;

	virtual void Tick(float DeltaTime) override;

	void UpdateMesh(int32 section);

	virtual void BeginPlay() override;
};
