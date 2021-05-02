// Fill out your copyright notice in the Description page of Project Settings.


#include "MediumHerbivoreCharacter.h"
#include "Vegetation.h"
#include "BaseCarnivoreCharacter.h"
#include "SmallCarnivoreCharacter.h"

AMediumHerbivoreCharacter::AMediumHerbivoreCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	//DinoCollision = CreateDefaultSubobject<UBoxComponent>(FName("Dino Collision"));
	VegetationCollision = CreateDefaultSubobject<UBoxComponent>(FName("Vegetation Collision"));
	VegetationCollision->InitBoxExtent(FVector(50, 50, 100));
	VegetationCollision->SetupAttachment(RootComponent);
	CarnivoreCollision = CreateDefaultSubobject<UBoxComponent>(FName("Carnivore Collision"));
	CarnivoreCollision->InitBoxExtent(FVector(50, 50, 100));
	CarnivoreCollision->SetupAttachment(RootComponent);
	health = 10;
	maxHealth = 10;
	hunger = 10;
	maxHunger = 10;
	slowSpeed = 300.0f;
	normalSpeed = 700.0f;
	isStarving = false;
	isInjured = false;
}

void AMediumHerbivoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMediumHerbivoreCharacter::healthAndHungerCycle, 2.0f, true, 5.0f);
	VegetationCollision->OnComponentBeginOverlap.AddDynamic(this, &AMediumHerbivoreCharacter::OnOverlapBegin);
	CarnivoreCollision->OnComponentBeginOverlap.AddDynamic(this, &AMediumHerbivoreCharacter::OnOverlapBegin);
}

void AMediumHerbivoreCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVegetation* Vegetation = Cast<AVegetation>(OtherActor);
	ABaseCarnivoreCharacter* Carnivore = Cast<ABaseCarnivoreCharacter>(OtherActor);

	if (Vegetation) 
	{
		incrementHunger();
		checkStarvingStatus();
		if (!isStarving)
			setMovementSpeedNormal();
	}
	else if (Carnivore)
	{
		if (!(Cast<ASmallCarnivoreCharacter>(OtherActor)))
		{
			const FVector ForwardDirection = Carnivore->GetRootComponent()->GetForwardVector();
			const FVector totalForce = ForwardDirection * 3000 + FVector(0, 0, 100);
			LaunchCharacter(totalForce, true, true);
			decrementHealth();
			if (health <= 0)
				Destroy();
			else
			{
				checkInjuryStatus();
				if (isInjured)
					setMovementSpeedSlow();
			}
		}
	}
}