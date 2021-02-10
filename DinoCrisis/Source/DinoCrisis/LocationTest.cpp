// Fill out your copyright notice in the Description page of Project Settings.


#include "LocationTest.h"

// Sets default values
ALocationTest::ALocationTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALocationTest::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("%d, %d, %d"), this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z);
	
}

// Called every frame
void ALocationTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

