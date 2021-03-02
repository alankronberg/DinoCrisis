// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseDinoController.h"
#include "BaseDinoChar.h"
#include "DinoTP.h"
#include "Engine.h"

ABaseDinoController::ABaseDinoController()
{
	BtComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BtComp"));
	BbComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BbComp"));

	LocationToGoKey = "LocationToGo";

	CurrentTargetPoint = 0;
}

void ABaseDinoController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADinoTP::StaticClass(), TargetPoint);
}

void ABaseDinoController::OnPossess(APawn* AIPawn)
{
	Super::OnPossess(AIPawn);

	ABaseDinoChar* AICharacter = Cast<ABaseDinoChar>(AIPawn);

	if (AICharacter) 
	{
		/*Blackboard initialization using base dino char class*/
		if (AICharacter->BehaviorTree->BlackboardAsset) 
		{
			BbComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		/*Fills target point array with all of the placed target points*/
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADinoTP::StaticClass(), TargetPoint);

		/*Startup Behavior Tree for a base dino char*/
		BtComp->StartTree(*AICharacter->BehaviorTree);
	}
}
