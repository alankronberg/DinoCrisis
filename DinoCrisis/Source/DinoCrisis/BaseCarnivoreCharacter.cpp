// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCarnivoreCharacter.h"
#include "BaseHerbivoreCharacter.h"

void ABaseCarnivoreCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseHerbivoreCharacter* Herbivore = Cast<ABaseHerbivoreCharacter>(OtherActor);
	if (Herbivore) {
		incrementHunger();
		checkStarvingStatus();
		if (!isStarving)
			setMovementSpeedNormal();
	}
}