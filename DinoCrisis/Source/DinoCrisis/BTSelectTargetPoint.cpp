// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectTargetPoint.h"
#include "DinoTP.h"
#include "BaseDinoController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseDinoController* Controller = Cast<ABaseDinoController>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		/*There is a blackboard comp connected to the character possessed by the controller. This gets it.*/
		UBlackboardComponent* BlackboardComp = Controller->GetBlackboardComponent();

		/*The current target point that will be used to navigate during the task. Will go to next until looping back*/
		ADinoTP* CurrentPoint = Cast<ADinoTP>(BlackboardComp->GetValueAsObject("LocationToGo"));

		/*Gets all the available target points*/
		TArray<AActor*> AvailableTargetPoints = Controller->GetTargetPoints();
		
		ADinoTP* NextTargetPoint = nullptr;

		/*if there are more available targets, move to the next one*/
		if (Controller->CurrentTargetPoint != AvailableTargetPoints.Num() - 1)
		{
			NextTargetPoint = Cast<ADinoTP>(AvailableTargetPoints[++Controller->CurrentTargetPoint]);
		}
		else /*else loop back and make the first target the next target point*/
		{
			NextTargetPoint = Cast<ADinoTP>(AvailableTargetPoints[0]);
			Controller->CurrentTargetPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
