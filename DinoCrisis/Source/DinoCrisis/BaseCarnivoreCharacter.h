// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDinoCharacter.h"
#include "BaseCarnivoreCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API ABaseCarnivoreCharacter : public ABaseDinoCharacter
{
	GENERATED_BODY()
	
	public:
		UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	protected:
		UPROPERTY(EditAnywhere)
		UBoxComponent* HerbivoreCollision = nullptr;
};
