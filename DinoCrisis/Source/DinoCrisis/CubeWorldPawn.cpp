// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeWorldPawn.h"

void ACubeWorldPawn::SaveGame() {
	//InputComponent->BindAction("Save", IE_Pressed, this, &ACubeWorldPawn::SaveGame); //This is what was causing performance issues. This LOC is not needed because of what I added in the BP
	//Creating an instance of SaveGameObject class
	USaveGameObject* SaveGameInstance = Cast<USaveGameObject>(UGameplayStatics::CreateSaveGameObject(USaveGameObject::StaticClass()));
	//Set the save game instance location equal to the player's current location
	SaveGameInstance->PlayerLocation = this->GetActorLocation();
	//Saving the chunks to the save game instance
	//SaveGameInstance->Chunks = TheseChunks.dumpChunkData();
	//Save Game Instance
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Slot1"), 0);
	//Logging a message showing we saved the game
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Game Saved."));
}

void ACubeWorldPawn::LoadGame() {
	//InputComponent->BindAction("Load", IE_Pressed, this, &ACubeWorldPawn::LoadGame); 
	//Creating an instance of SaveGameObject class
	USaveGameObject* SaveGameInstance = Cast<USaveGameObject>(UGameplayStatics::CreateSaveGameObject(USaveGameObject::StaticClass()));
	//Load the save game into savegameinstance variable
	SaveGameInstance = Cast<USaveGameObject>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
	//Set the player's position from the saved game file
	this->SetActorLocation(SaveGameInstance->PlayerLocation);
	//Initializing the chunks
	//TheseChunks.fillChunkData(SaveGameInstance->Chunks);
	//Logging a message showing we loaded the game
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Game Loaded."));
}