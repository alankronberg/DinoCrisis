// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine.h>
#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "VoxelCube.generated.h"

struct FPointData {
	FVector points[8];


	float values[8];
};

UCLASS()
class DINOCRISIS_API AVoxelCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelCube();

	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* PMC;

	TArray<UBoxComponent*> cornerBoxes;

	UPROPERTY()
	FPointData cornerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
		UMaterial* material;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	const int32 OFFSET = 50;
public:
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	class AVoxelChunk* parent;
	int32 section;

protected:
	int isoLevel = 0;

	void UpdateMesh();

	void MarchingCubes();

	FVector Midpoint(FVector point1, FVector point2);

	void incrementCorner0();
	void incrementCorner1();
	void incrementCorner2();
	void incrementCorner3();
	void incrementCorner4();
	void incrementCorner5();
	void incrementCorner6();
	void incrementCorner7();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitMesh();

};
