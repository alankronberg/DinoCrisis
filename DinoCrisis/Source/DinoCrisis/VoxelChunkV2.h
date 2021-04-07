// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Components/BoxComponent.h"
#include "VoxelChunkV2.generated.h"

struct Cube {
	int32 corners[8][3];
};

UCLASS()
class DINOCRISIS_API AVoxelChunkV2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelChunkV2();

	UPROPERTY(BlueprintReadWrite)
	class UProceduralMeshComponent* PMC;

	int32 cornerValues[11][11][11];
	Cube cubes[1000];

	bool isDirty = false;

	UBoxComponent* hitBox;

	FVector rootLoc;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int isoLevel = 0;



	void MarchingCubes();

	FVector Midpoint(FVector point1, FVector point2);


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
