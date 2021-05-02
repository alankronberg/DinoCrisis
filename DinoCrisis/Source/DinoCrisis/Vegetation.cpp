// Fill out your copyright notice in the Description page of Project Settings.


#include "Vegetation.h"
#include "BaseHerbivoreCharacter.h"
#include "DinoCrisisGameModeBase.h"

// Sets default values
AVegetation::AVegetation()
{
	HerbivoreCollision = CreateDefaultSubobject<UBoxComponent>(FName("Herbivore Collision"));
	HerbivoreCollision->InitBoxExtent(FVector(50, 50, 50));
	HerbivoreCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AVegetation::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	gameMode = Cast<ADinoCrisisGameModeBase>(world->GetAuthGameMode());
	if (world)
	{
		if (gameMode)
		{
			gameMode->allVegetation.Add(this);
		}
	}
	HerbivoreCollision->OnComponentBeginOverlap.AddDynamic(this, &AVegetation::OnOverlapBegin);
}

void AVegetation::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseHerbivoreCharacter* Herbivore = Cast<ABaseHerbivoreCharacter>(OtherActor);
	if (Herbivore)
		Destroy();
}