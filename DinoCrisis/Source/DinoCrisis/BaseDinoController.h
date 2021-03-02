// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseDinoController.generated.h"

/**
 * 
 */
UCLASS()
class DINOCRISIS_API ABaseDinoController : public AAIController
{
	GENERATED_BODY()

		void Tick(float DeltaTime);

		/*Behavior Tree and Blackboard Components*/
		UBehaviorTreeComponent* BtComp;
		UBlackboardComponent* BbComp;

		/*Blackboard keys: used as a way to pass something between blackboard and the behavior tree*/
		UPROPERTY(EditDefaultsOnly, Category = AI)
		FName LocationToGoKey;

		/*Stores target points. Gets the actor and stores it in the array, then gets the next target point*/
		TArray<AActor*> TargetPoint;

		virtual void OnPossess(APawn* AIPawn) override;

		/*tracks current target point. will be used to loop back around to first target point once last one is reached*/

public: 

	ABaseDinoController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BbComp; }
	FORCEINLINE TArray<AActor*> GetTargetPoints() const { return TargetPoint; }

	int32 CurrentTargetPoint = 0;
	
};
