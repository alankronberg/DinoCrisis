// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunk.h"
#include "Engine/World.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AVoxelChunk::AVoxelChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PMC = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
	RootComponent = PMC;
	PMC->bUseAsyncCooking = true;
	
}

void AVoxelChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isDirty) {
		Vertices.Reset();
		Triangles.Reset();
		PMC->ClearAllMeshSections();
		for (int i = 0; i < 1000; i++) {
			if (sectionData.cubes[i]) {
				for (FVector vertex : sectionData.cubes[i]->Vertices) {
					Vertices.Add(sectionData.locations[i] + vertex);
				}
			}
		}
		for (int i = 0; i < Vertices.Num(); i += 3) {
			Triangles.Add(i);
			Triangles.Add(i + 2);
			Triangles.Add(i + 1);
		}

		PMC->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
		isDirty = false;
	}
	

}

void AVoxelChunk::UpdateMesh(int32 section)
{
	isDirty = true;
	
	
}

void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
	int sect = 0;
	for (int z = -400; z < 600; z = z + 100) {
		for (int y = -400; y < 600; y += 100) {
			for (int x = -400; x < 600; x += 100) {
				FVector spawnLoc(GetActorLocation().X + x, GetActorLocation().Y + y, GetActorLocation().Z + z);
				FRotator spawnRot(0.f, 0.f, 0.f);
				FActorSpawnParameters spawnInfo = FActorSpawnParameters();
				AVoxelCube* cube = GetWorld()->SpawnActor<AVoxelCube>(spawnLoc, spawnRot, spawnInfo);
				cube->parent = this;
				sectionData.cubes[sect] = cube;
				sectionData.locations[sect] = FVector(x, y, z);
				cube->section = sect++;
				cube->InitMesh();
				
			}
		}
	}
	
}
