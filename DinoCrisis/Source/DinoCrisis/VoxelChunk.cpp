// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunk.h"
#include "Engine/World.h"
#include "KismetProceduralMeshLibrary.h"
#include "NavigationSystem.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

// Sets default values
AVoxelChunk::AVoxelChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PMC = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
	RootComponent = PMC;
	PMC->bUseAsyncCooking = true;

	int cLoc = 0;
	for (int z = -400; z < 600; z = z + 100) {
		for (int y = -400; y < 600; y += 100) {
			for (int x = -400; x < 600; x += 100) {
				sectionData.locations[cLoc++] = FVector(x, y, z);

			}
		}
	}

	for (int i = 0; i < 1000; i++) {
		FName id = *FString::Printf(TEXT("Cube%d"), i);
		sectionData.cubes[i] = CreateDefaultSubobject<UCubeSceneComponent>(id);		
		sectionData.cubes[i]->SetupAttachment(RootComponent);
		sectionData.cubes[i]->SetWorldLocation(sectionData.locations[i], false);
		sectionData.cubes[i]->SetComponentTickEnabled(false);
		sectionData.cubes[i]->parent = this;
		sectionData.cubes[i]->section = i;
		sectionData.cubes[i]->InitMesh();
	}
	Tick(0.0);

}

void AVoxelChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isDirty) {
		Vertices.Reset();
		Triangles.Reset();
		UVs.Reset();
		Normals.Reset();
		Tangents.Reset();
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
			UVs.Add(FVector2D(0.f, 0.f));
			UVs.Add(FVector2D(0.f, 1.f));
			UVs.Add(FVector2D(1.f, 0.f));
		}

		UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVs, Normals, Tangents);

		PMC->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), Tangents, true);
		FNavigationSystem::UpdateComponentData(*PMC);
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
	/*int sect = 0;
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
	}*/

}

TArray<float> AVoxelChunk::dumpChunkData()
{
	TArray<float> chunkData;
	for (UCubeSceneComponent* cube : sectionData.cubes) {
		for (float value : cube->cornerData.values) {
			chunkData.Add(value);
		}
	}
	return chunkData;
}

void AVoxelChunk::fillChunkData(TArray<float> chunkData)
{
	int cubeIndx = 0;
	TArray<float> values;
	for (int i = 0; i < chunkData.Num(); i = i + 8) {
		for (int j = i; j < (i + 8); j++) {
			values.Add(chunkData[j]);
		}
		sectionData.cubes[cubeIndx]->fillValues(values);
		sectionData.cubes[cubeIndx]->UpdateMesh();
		values.Reset();
		cubeIndx++;
	}
}

void AVoxelChunk::WriteTest()
{
	UE_LOG(LogTemp, Warning, TEXT("Inside WriteTest()"));
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/MapData.map");
	FString FileContent;
	for (UCubeSceneComponent* cube : sectionData.cubes) {
		if (cube) {
			FileContent += cube->dumpValues();
		}
	}
	FileContent += TEXT(";");
	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void AVoxelChunk::Overwrite()
{
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/MapData.map");
	FString FileContent;
	for (UCubeSceneComponent* cube : sectionData.cubes) {
		if (cube) {
			FileContent += cube->dumpValues();
		}
	}
	FileContent += TEXT(";");
	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get());
}

void AVoxelChunk::InitCubesFromFile(TArray<FString> values)
{
	UE_LOG(LogTemp, Warning, TEXT("Inside InitCubesFromFile"));
	int cubeIndx = 0;
	for (int i = 0; i < values.Num(); i += 8) {
		TArray<float> cornerVals;
		for (int j = 0; j < 8; j++) {
			cornerVals.Add(FCString::Atof(*values[j + i]));
		}
		sectionData.cubes[cubeIndx]->fillValues(cornerVals);
		sectionData.cubes[cubeIndx++]->UpdateMesh();
	}

}