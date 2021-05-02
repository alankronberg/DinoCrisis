// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHerbivoreCharacter.h"
#include "LargeHerbivoreCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API ALargeHerbivoreCharacter : public ABaseHerbivoreCharacter
{
	GENERATED_BODY()
	
	public:
		ALargeHerbivoreCharacter();
		UFUNCTION()
			void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	protected:
		void BeginPlay();
};
