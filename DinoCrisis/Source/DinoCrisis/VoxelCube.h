// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine.h>
#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "VoxelCube.generated.h"

USTRUCT()
struct FPointData {
	GENERATED_BODY()
public:
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
	class USceneComponent* root;

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
	void UpdateMesh();
protected:
	int isoLevel = 0;

	

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

	void incrementCorner(int corner, int value);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString dumpValues();

	void fillValues(TArray<float> values);

	void InitMesh();

};
