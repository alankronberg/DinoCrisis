// Copyright Epic Games, Inc. All Rights Reserved.


#include "DinoCrisisGameModeBase.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/Char.h"
#include "Kismet/GameplayStatics.h"

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

TArray<int32> ADinoCrisisGameModeBase::getIntsFromString(FString input)
{
	TArray<int32> output;
	//for each (TCHAR digit in input.GetCharArray()) {
	//	UE_LOG(LogTemp, Warning, TEXT("%c"), digit);
	//}
	for (int i = 0; i < input.Len(); i++) {
		output.Add((static_cast<int32>(input[i]) - static_cast<int32>('0')));
		
	}
	return output;
}
