// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunkV2.h"
#include "KismetProceduralMeshLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Engine/World.h"
#include "DinoCrisisGameModeBase.h"
#include "CubeWorldPawn.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

static int edgeTable1[256][16] = {
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1 },
	{ 8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1 },
	{ 3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1 },
	{ 4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1 },
	{ 4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1 },
	{ 9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1 },
	{ 10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1 },
	{ 5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1 },
	{ 5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1 },
	{ 8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1 },
	{ 2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1 },
	{ 2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1 },
	{ 11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1 },
	{ 5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1 },
	{ 11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1 },
	{ 11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1 },
	{ 2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1 },
	{ 6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1 },
	{ 3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1 },
	{ 6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1 },
	{ 6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1 },
	{ 8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1 },
	{ 7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1 },
	{ 3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1 },
	{ 0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1 },
	{ 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1 },
	{ 8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1 },
	{ 5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1 },
	{ 0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1 },
	{ 6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1 },
	{ 10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1 },
	{ 1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1 },
	{ 0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1 },
	{ 3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1 },
	{ 6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1 },
	{ 9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1 },
	{ 8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1 },
	{ 3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1 },
	{ 10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1 },
	{ 10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1 },
	{ 2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1 },
	{ 7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1 },
	{ 2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1 },
	{ 1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1 },
	{ 11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1 },
	{ 8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1 },
	{ 0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1 },
	{ 7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1 },
	{ 7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1 },
	{ 10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1 },
	{ 0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1 },
	{ 7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1 },
	{ 6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1 },
	{ 4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1 },
	{ 10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1 },
	{ 8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1 },
	{ 1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1 },
	{ 10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1 },
	{ 10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1 },
	{ 9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1 },
	{ 7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1 },
	{ 3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1 },
	{ 7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1 },
	{ 3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1 },
	{ 6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1 },
	{ 9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1 },
	{ 1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1 },
	{ 4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1 },
	{ 7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1 },
	{ 6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1 },
	{ 0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1 },
	{ 6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1 },
	{ 0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1 },
	{ 11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1 },
	{ 6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1 },
	{ 5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1 },
	{ 9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1 },
	{ 1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1 },
	{ 10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1 },
	{ 0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1 },
	{ 11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1 },
	{ 9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1 },
	{ 7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1 },
	{ 2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1 },
	{ 9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1 },
	{ 9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1 },
	{ 1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1 },
	{ 0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1 },
	{ 10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1 },
	{ 2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1 },
	{ 0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1 },
	{ 0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1 },
	{ 9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1 },
	{ 5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1 },
	{ 5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1 },
	{ 8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1 },
	{ 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1 },
	{ 1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1 },
	{ 3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1 },
	{ 4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1 },
	{ 9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1 },
	{ 11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1 },
	{ 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1 },
	{ 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1 },
	{ 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1 },
	{ 1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1 },
	{ 4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1 },
	{ 0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1 },
	{ 1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
};


// Sets default values
AVoxelChunkV2::AVoxelChunkV2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PMC = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
	RootComponent = PMC;
	PMC->bUseAsyncCooking = true;
	PMC->SetCullDistance(10000.0f);
	
	rootLoc = GetActorLocation();
	
	int hSize = CUBES_PER_SIDE / 2 * CUBE_SIZE;

	hitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	hitBox->SetupAttachment(RootComponent);
	hitBox->SetGenerateOverlapEvents(true);
	hitBox->SetCollisionProfileName(TEXT("Terrain"));
	hitBox->OnComponentBeginOverlap.AddDynamic(this, &AVoxelChunkV2::OnOverlapBegin);
	hitBox->SetComponentTickEnabled(false);
	hitBox->SetWorldLocation(GetActorLocation() + FVector(hSize, hSize, hSize), false);
	hitBox->SetBoxExtent(FVector(hSize - CUBE_SIZE, hSize - CUBE_SIZE, hSize - CUBE_SIZE));
	//hitBox->SetHiddenInGame(false);
	Vertices.Reserve(MAX_VERTS);
	Triangles.Reserve(MAX_VERTS);
	UVs.Reserve(MAX_VERTS);


	for (int z = 0; z < CUBES_PER_SIDE + 1; z++) {
		for (int y = 0; y < CUBES_PER_SIDE + 1; y++) {
			for (int x = 0; x < CUBES_PER_SIDE + 1; x++) {
				if (z == 0) {
					cornerValues[x][y][z] = 1;
				}
				else {
					cornerValues[x][y][z] = 0;
				}
			}
		}
	}

	//for (int z = 0; z < CUBES_PER_SIDE; z++) {
		for (int y = 0; y < CUBES_PER_SIDE; y++) {
			for (int x = 0; x < CUBES_PER_SIDE; x++) {
				MarchingCubes(x, y, 0);
			}
		}
	//}


		float uvSpacing = 1 / CUBES_PER_SIDE;
	//for (int z = 0; z < CUBES_PER_SIDE; z++) {
		for (int y = 0; y < CUBES_PER_SIDE; y++) {
			for (int x = 0; x < CUBES_PER_SIDE; x++) {
				Vertices.Append(cubeVerts[x][y][0]);
			}
		}
	//}
	for (int i = 0; i < Vertices.Num(); i += 3) {
		Triangles.Add(i);
		Triangles.Add(i + 2);
		Triangles.Add(i + 1);
		if (Vertices[i].X == Vertices[i + 1].X) {
			UVs.Add(FVector2D(0.f, 0.f));
			UVs.Add(FVector2D(0.f, 1.f));
			UVs.Add(FVector2D(1.f, 0.f));
		}
		else {
			UVs.Add(FVector2D(1.f, 0.f));
			UVs.Add(FVector2D(0.f, 0.f));
			UVs.Add(FVector2D(0.f, 1.f));
		}
		
	}
	PMC->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), Tangents, true);
	FNavigationSystem::UpdateComponentData(*PMC);
	
}

// Called when the game starts or when spawned
void AVoxelChunkV2::BeginPlay()
{
	Super::BeginPlay();
	ADinoCrisisGameModeBase* gm = (ADinoCrisisGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->chunks.Add(this);

}

void AVoxelChunkV2::MarchingCubes(int tX, int tY, int tZ)
{
	for (int z = FMath::Clamp(tZ - 1, 0, CUBES_PER_SIDE); z < tZ + 1 && z < CUBES_PER_SIDE; z++) {
		for (int y = FMath::Clamp(tY - 1, 0, CUBES_PER_SIDE); y < tY + 1 && y < CUBES_PER_SIDE; y++) {
			for (int x = FMath::Clamp(tX - 1, 0, CUBES_PER_SIDE); x < tX + 1 && x < CUBES_PER_SIDE; x++) {
				TArray<FVector>* Verts = &(cubeVerts[x][y][z]);
				Verts->Reset(15);
				int cubeIndex = 0;
				int x0 = x;
				int y0 = y;
				int z0 = z;
				int x1 = x + 1;
				int y1 = y;
				int z1 = z;
				int x2 = x + 1;
				int y2 = y + 1;
				int z2 = z;
				int x3 = x;
				int y3 = y + 1;
				int z3 = z;
				int x4 = x;
				int y4 = y;
				int z4 = z + 1;
				int x5 = x + 1;
				int y5 = y;
				int z5 = z + 1;
				int x6 = x + 1;
				int y6 = y + 1;
				int z6 = z + 1;
				int x7 = x;
				int y7 = y + 1;
				int z7 = z + 1;
				if (cornerValues[x0][y0][z0] <= isoLevel) {
					cubeIndex += pow(2, 0);
				}
				if (cornerValues[x1][y1][z1] <= isoLevel) {
					cubeIndex += pow(2, 1);
				}
				if (cornerValues[x2][y2][z2] <= isoLevel) {
					cubeIndex += pow(2, 2);
				}
				if (cornerValues[x3][y3][z3] <= isoLevel) {
					cubeIndex += pow(2, 3);
				}
				if (cornerValues[x4][y4][z4] <= isoLevel) {
					cubeIndex += pow(2, 4);
				}
				if (cornerValues[x5][y5][z5] <= isoLevel) {
					cubeIndex += pow(2, 5);
				}
				if (cornerValues[x6][y6][z6] <= isoLevel) {
					cubeIndex += pow(2, 6);
				}
				if (cornerValues[x7][y7][z7] <= isoLevel) {
					cubeIndex += pow(2, 7);
				}
				if (cubeIndex != 0 && cubeIndex != 255) {
					int* tEdges = edgeTable1[cubeIndex];
					for (int j = 0; *(tEdges + j) != -1; j++) {
						if (*(tEdges + j) == 0) {
							Verts->Add(Midpoint(rootLoc + (FVector(x0, y0, z0) * CUBE_SIZE), rootLoc + (FVector(x1, y1, z1) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 1) {
							Verts->Add(Midpoint(rootLoc + (FVector(x1, y1, z1) * CUBE_SIZE), rootLoc + (FVector(x2, y2, z2) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 2) {
							Verts->Add(Midpoint(rootLoc + (FVector(x2, y2, z2) * CUBE_SIZE), rootLoc + (FVector(x3, y3, z3) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 3) {
							Verts->Add(Midpoint(rootLoc + (FVector(x3, y3, z3) * CUBE_SIZE), rootLoc + (FVector(x0, y0, z0) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 4) {
							Verts->Add(Midpoint(rootLoc + (FVector(x4, y4, z4) * CUBE_SIZE), rootLoc + (FVector(x5, y5, z5) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 5) {
							Verts->Add(Midpoint(rootLoc + (FVector(x5, y5, z5) * CUBE_SIZE), rootLoc + (FVector(x6, y6, z6) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 6) {
							Verts->Add(Midpoint(rootLoc + (FVector(x6, y6, z6) * CUBE_SIZE), rootLoc + (FVector(x7, y7, z7) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 7) {
							Verts->Add(Midpoint(rootLoc + (FVector(x7, y7, z7) * CUBE_SIZE), rootLoc + (FVector(x4, y4, z4) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 8) {
							Verts->Add(Midpoint(rootLoc + (FVector(x4, y4, z4) * CUBE_SIZE), rootLoc + (FVector(x0, y0, z0) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 9) {
							Verts->Add(Midpoint(rootLoc + (FVector(x5, y5, z5) * CUBE_SIZE), rootLoc + (FVector(x1, y1, z1) * CUBE_SIZE)));
						}
						else if (*(tEdges + j) == 10) {
							Verts->Add(Midpoint(rootLoc + (FVector(x6, y6, z6) * CUBE_SIZE), rootLoc + (FVector(x2, y2, z2) * CUBE_SIZE)));
						}
						else {
							Verts->Add(Midpoint(rootLoc + (FVector(x7, y7, z7) * CUBE_SIZE), rootLoc + (FVector(x3, y3, z3) * CUBE_SIZE)));
						}
					}
				}
			}
		}
	}
}

FVector AVoxelChunkV2::Midpoint(FVector point1, FVector point2)
{
	FVector midPoint;
	midPoint.X = (point1.X + point2.X) / 2;
	midPoint.Y = (point1.Y + point2.Y) / 2;
	midPoint.Z = (point1.Z + point2.Z) / 2;
	return midPoint;
}

void AVoxelChunkV2::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Occured"));
	if (ACubeWorldPawn* player = Cast<ACubeWorldPawn>(OtherActor)) {
		FVector target;
		//USceneComponent* cube = OtherComp->GetChildComponent(1);
		if (player->incrementValue == 1) {
			target = player->incrementActor->GetComponentLocation() - GetActorLocation();
		}
		else {
			target = player->decrementActor->GetComponentLocation() - GetActorLocation();
		}
		
		dusts.Enqueue(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), dust, OtherComp->GetComponentLocation()));
		int32 x = target.X;
		int32 y = target.Y;
		int32 z = target.Z;
		if (x % CUBE_SIZE >= CUBE_SIZE / 2) {
			x = FMath::Clamp(x / CUBE_SIZE + 1, 1, CUBES_PER_SIDE - 1);
		}
		else {
			x = FMath::Clamp(x / CUBE_SIZE, 1, CUBES_PER_SIDE - 1);
		}
		if (y % CUBE_SIZE >= CUBE_SIZE / 2) {
			y = FMath::Clamp(y / CUBE_SIZE + 1, 1, CUBES_PER_SIDE - 1);
		}
		else {
			y = FMath::Clamp(y / CUBE_SIZE, 1, CUBES_PER_SIDE - 1);
		}
		if (z % CUBE_SIZE >= CUBE_SIZE / 2) {
			z = FMath::Clamp(z / CUBE_SIZE + 1, 1, CUBES_PER_SIDE - 1);
		}
		else {
			z = FMath::Clamp(z / CUBE_SIZE, 1, CUBES_PER_SIDE);
		}
		
		ChangeMade.Enqueue(FVector(x,y,z));
		Values.Enqueue(player->incrementValue);
		
	}
}

// Called every frame
void AVoxelChunkV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FinishedChange.IsEmpty()) {
		PMC->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), Tangents, true);
		FNavigationSystem::UpdateComponentData(*PMC);
		int32 test1;
		UParticleSystemComponent* curDust;
		dusts.Dequeue(curDust);
		curDust->DestroyComponent();
		FinishedChange.Dequeue(test1);
		OnGoingChange.Dequeue(test1);
	}
	else if (!ChangeMade.IsEmpty() && OnGoingChange.IsEmpty()){
		FVector point;
		float value;
		ChangeMade.Dequeue(point);
		Values.Dequeue(value);
		if (cornerValues[int(point.X)][int(point.Y)][int(point.Z)] == value) {
			UParticleSystemComponent* curDust;
			dusts.Dequeue(curDust);
			curDust->DestroyComponent();
		}
		else {
			cornerValues[int(point.X)][int(point.Y)][int(point.Z)] = FMath::Clamp(float(cornerValues[int(point.X)][int(point.Y)][int(point.Z)]) + value, 0.f, 1.f);
			MarchingCubes(point.X, point.Y, point.Z);
			(new FAutoDeleteAsyncTask<MeshCalculator>(this))->StartBackgroundTask();
			OnGoingChange.Enqueue(1);
		}
	}
}

TArray<int32> AVoxelChunkV2::dumpChunkData()
{
	TArray<int32> chunkData;
	for (int32 x = 0; x <= CUBES_PER_SIDE; x++) {
		for (int32 y = 0; y <= CUBES_PER_SIDE; y++) {
			for (int32 z = 0; z <= CUBES_PER_SIDE; z++) {
				chunkData.Add(cornerValues[x][y][z]);
			}
		}
	}
	return chunkData;
}

void AVoxelChunkV2::fillChunkData(TArray<int32> chunkData)
{
	Vertices.Reset(MAX_VERTS);
	Triangles.Reset(MAX_VERTS);
	UVs.Reset(MAX_VERTS);
	Normals.Reset();
	Tangents.Reset();
	int32 index = 0;
	for (int32 x = 0; x <= CUBES_PER_SIDE; x++) {
		for (int32 y = 0; y <= CUBES_PER_SIDE; y++) {
			for (int32 z = 0; z <= CUBES_PER_SIDE; z++) {
				cornerValues[x][y][z] = chunkData[index++];
			}
		}
	}

	for (int z = 0; z < CUBES_PER_SIDE; z++) {
		for (int y = 0; y < CUBES_PER_SIDE; y++) {
			for (int x = 0; x < CUBES_PER_SIDE; x++) {
				MarchingCubes(x, y, z);
			}
		}
	}



	for (int z = 0; z < CUBES_PER_SIDE; z++) {
		for (int y = 0; y < CUBES_PER_SIDE; y++) {
			for (int x = 0; x < CUBES_PER_SIDE; x++) {
				Vertices.Append(cubeVerts[x][y][z]);
			}
		}
	}
	for (int i = 0; i < Vertices.Num(); i += 3) {
		Triangles.Add(i);
		Triangles.Add(i + 2);
		Triangles.Add(i + 1);
		/*FVector ab = Vertices[i + 1] - Vertices[i];
		FVector ac = Vertices[i + 2] - Vertices[i];
		FVector normal = FVector::CrossProduct(ab, ac);
		normal.Normalize();
		Normals.Add(normal);
		Normals.Add(normal);
		Normals.Add(normal);
		Tangents.Add(FProcMeshTangent(1.0f, 0.0f, 0.0f));
		Tangents.Add(FProcMeshTangent(1.0f, 0.0f, 0.0f));
		Tangents.Add(FProcMeshTangent(1.0f, 0.0f, 0.0f));*/
		if (Vertices[i].X == Vertices[i + 1].X) {
			UVs.Add(FVector2D(0.f, 0.f));
			UVs.Add(FVector2D(0.f, 1.f));
			UVs.Add(FVector2D(1.f, 0.f));
		}
		else {
			UVs.Add(FVector2D(1.f, 0.f));
			UVs.Add(FVector2D(0.f, 0.f));
			UVs.Add(FVector2D(0.f, 1.f));
		}
	}
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVs, Normals, Tangents);
	PMC->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), Tangents, true);
	FNavigationSystem::UpdateComponentData(*PMC);
}

void AVoxelChunkV2::Write()
{
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/MapData.map");
	FString FileContent;
	for (int32 x = 0; x <= CUBES_PER_SIDE; x++) {
		for (int32 y = 0; y <= CUBES_PER_SIDE; y++) {
			for (int32 z = 0; z <= CUBES_PER_SIDE; z++) {
				FileContent += (FString::FromInt(cornerValues[x][y][z]) + TEXT(","));
			}
		}
	}
	FileContent += TEXT("\n");
	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void AVoxelChunkV2::Overwrite()
{
}

void AVoxelChunkV2::InitCubesFromFile(TArray<FString> values)
{
}


void MeshCalculator::DoWork()
{
	UE_LOG(LogTemp, Warning, TEXT("IN WORKER THREAD"));
	chunk->Vertices.Reset(MAX_VERTS);
	chunk->Triangles.Reset(MAX_VERTS);
	chunk->UVs.Reset(MAX_VERTS);
	chunk->Normals.Reset();
	chunk->Tangents.Reset();
	float uvSpacing = 1 / (CUBES_PER_SIDE * CUBE_SIZE);
	for (int z = 0; z < CUBES_PER_SIDE; z++) {
		for (int y = 0; y < CUBES_PER_SIDE; y++) {
			for (int x = 0; x < CUBES_PER_SIDE; x++) {
				chunk->Vertices.Append(chunk->cubeVerts[x][y][z]);
			}
		}
	}
	for (int i = 0; i < chunk->Vertices.Num(); i += 3) {
		chunk->Triangles.Add(i);
		chunk->Triangles.Add(i + 2);
		chunk->Triangles.Add(i + 1);
		if (chunk->Vertices[i].X == chunk->Vertices[i + 1].X) {
			chunk->UVs.Add(FVector2D(0.f, 0.f));
			chunk->UVs.Add(FVector2D(0.f, 1.f));
			chunk->UVs.Add(FVector2D(1.f, 0.f));
		}
		else {
			chunk->UVs.Add(FVector2D(1.f, 0.f));
			chunk->UVs.Add(FVector2D(0.f, 0.f));
			chunk->UVs.Add(FVector2D(0.f, 1.f));
		}
	}

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(chunk->Vertices, chunk->Triangles, chunk->UVs, chunk->Normals, chunk->Tangents);
	chunk->FinishedChange.Enqueue(1);
	
}
