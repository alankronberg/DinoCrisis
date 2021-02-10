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
	
}

void AVoxelChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	

}

void AVoxelChunk::UpdateMesh(int32 section)
{
	Vertices.Reset();
	Triangles.Reset();
	PMC->ClearAllMeshSections();
	for (AVoxelCube* cube : cubes) {
		for (FVector vertex : cube->Vertices) {
			UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), vertex.X, vertex.Y, vertex.Z);
			Vertices.Add(vertex);
		}
	}
	for (int i = 0; i < Vertices.Num(); i += 3) {
		Triangles.Add(i);
		Triangles.Add(i + 2);
		Triangles.Add(i + 1);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Chunk update: Vertex count: %d Triangle Count: %d"), Vertices.Num(), Triangles.Num());
	
	
	PMC->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
	
}

void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
	int sect = 0;
	/*for (int z = -200; z < 300; z = z + 100) {*/
		for (int y = -100; y < 200; y += 100) {
			//for (int x = -200; x < 300; x += 100) {
				FVector spawnLoc(GetActorLocation().X, GetActorLocation().Y + y, GetActorLocation().Z);
				FRotator spawnRot(0.f, 0.f, 0.f);
				FActorSpawnParameters spawnInfo = FActorSpawnParameters();
				AVoxelCube* cube = GetWorld()->SpawnActor<AVoxelCube>(spawnLoc, spawnRot, spawnInfo);
				cubes.Add(cube);
				cube->parent = this;
				cube->section = sect++;
				cube->InitMesh();
				
			//}
		}
	/*}*/
	
}
