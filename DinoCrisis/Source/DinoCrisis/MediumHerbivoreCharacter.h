// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHerbivoreCharacter.h"
#include "MediumHerbivoreCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API AMediumHerbivoreCharacter : public ABaseHerbivoreCharacter
{
	GENERATED_BODY()
	
	public:
		AMediumHerbivoreCharacter();
		UFUNCTION()
			void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	protected:
		void BeginPlay();

};
