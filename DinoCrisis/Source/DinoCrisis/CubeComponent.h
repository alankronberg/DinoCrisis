// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Engine.h>
#include "Components/BoxComponent.h"
#include "CubeComponent.generated.h"


USTRUCT(BlueprintType)
struct FPointData {
	GENERATED_BODY()
public:
	FVector points[8];


	float values[8];
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DINOCRISIS_API UCubeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCubeComponent();

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* root;

	TArray<UBoxComponent*> cornerBoxes;

	UPROPERTY(BlueprintReadOnly)
		FPointData cornerData;

protected:
	// Called when the game starts
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
	

	FString dumpValues();

	void fillValues(TArray<float> values);

	void InitMesh();
		
};
