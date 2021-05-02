// Fill out your copyright notice in the Description page of Project Settings.


#include "LargeHerbivoreCharacter.h"
#include "Vegetation.h"
#include "LargeCarnivoreCharacter.h"

ALargeHerbivoreCharacter::ALargeHerbivoreCharacter()
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
	health = 20;
	maxHealth = 20;
	hunger = 20;
	maxHunger = 20;
	slowSpeed = 50.0f;
	normalSpeed = 100.0f;
	isStarving = false;
	isInjured = false;
}

void ALargeHerbivoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ALargeHerbivoreCharacter::healthAndHungerCycle, 2.0f, true, 5.0f);
	VegetationCollision->OnComponentBeginOverlap.AddDynamic(this, &ALargeHerbivoreCharacter::OnOverlapBegin);
	CarnivoreCollision->OnComponentBeginOverlap.AddDynamic(this, &ALargeHerbivoreCharacter::OnOverlapBegin);
}

void ALargeHerbivoreCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVegetation* Vegetation = Cast<AVegetation>(OtherActor);
	ALargeCarnivoreCharacter* LargeCarnivore = Cast<ALargeCarnivoreCharacter>(OtherActor);

	if (Vegetation)
	{
		incrementHunger();
		checkStarvingStatus();
		if (!isStarving)
			setMovementSpeedNormal();
	}
	else if (LargeCarnivore)
	{
		const FVector ForwardDirection = LargeCarnivore->GetRootComponent()->GetForwardVector();
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
