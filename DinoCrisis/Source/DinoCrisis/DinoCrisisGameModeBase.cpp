// Copyright Epic Games, Inc. All Rights Reserved.


#include "DinoCrisisGameModeBase.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

FString ADinoCrisisGameModeBase::getMapDataFromFile()
{
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/MapData.map");
	FString FileContent;
	FFileHelper::LoadFileToString(FileContent, *FilePath);
	return FileContent;
}

void ADinoCrisisGameModeBase::logMessage(FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(message));
}
