// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "ProceduralMeshComponent.h"
#include "Components/BoxComponent.h"
#include "VoxelChunkV2.generated.h"


const int CUBES_PER_SIDE = 40;
const int CUBE_SIZE = 100;
const int MAX_VERTS = 15 * CUBES_PER_SIDE * CUBES_PER_SIDE * CUBES_PER_SIDE;

const int NUM_CUBES = CUBES_PER_SIDE * CUBES_PER_SIDE * CUBES_PER_SIDE;

UCLASS()
class DINOCRISIS_API AVoxelChunkV2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelChunkV2();

	UPROPERTY(BlueprintReadWrite)
	class UProceduralMeshComponent* PMC;


	UPROPERTY(EditAnywhere)
	class UParticleSystem* dust;

	int32 cornerValues[CUBES_PER_SIDE + 1][CUBES_PER_SIDE + 1][CUBES_PER_SIDE + 1];
	TArray<FVector> cubeVerts[CUBES_PER_SIDE][CUBES_PER_SIDE][CUBES_PER_SIDE];



	

	UBoxComponent* hitBox;

	FVector rootLoc;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;

	TQueue<FVector> ChangeMade;
	TQueue<float> Values;
	TQueue<int32> OnGoingChange;
	TQueue<int32> FinishedChange;
	TQueue<UParticleSystemComponent*> dusts;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int isoLevel = 0;



	void MarchingCubes(int tX, int tY, int tZ);

	FVector Midpoint(FVector point1, FVector point2);


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TArray<int32> dumpChunkData();

	UFUNCTION(BlueprintCallable)
	void fillChunkData(TArray<int32> chunkData);

	UFUNCTION(BlueprintCallable)
	void Write();

	UFUNCTION(BlueprintCallable)
	void Overwrite();

	UFUNCTION(BlueprintCallable)
	void InitCubesFromFile(TArray<FString> values);

};


class MeshCalculator : public FNonAbandonableTask
{
	AVoxelChunkV2* chunk;

public:
	/*Default constructor*/
	MeshCalculator(AVoxelChunkV2* chunk)
	{
		UE_LOG(LogTemp, Warning, TEXT("Beginning OF THREAD CONSTRUCTOR"));
		this->chunk = chunk;
	}

	//his function is needed from the API of the engine.
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MeshCalculator, STATGROUP_ThreadPoolAsyncTasks);
	}

	/*This function is executed when we tell our task to execute*/
	void DoWork();
};