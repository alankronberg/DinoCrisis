// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayerPawn.h"
#include "Engine.h"

// Sets default values
AVRPlayerPawn::AVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Player Pawn Base Begin Play", true);

}

// Called when the game starts or when spawned
void AVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

