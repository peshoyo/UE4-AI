// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ActivateSkill.h"
#include "Controllers/Guard_AIController.h"


EBTNodeResult::Type UBTTask_ActivateSkill::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AGuard_AIController * Controller = Cast<AGuard_AIController>(OwnerComp.GetOwner());
	if (IsValid(Controller) == false)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* EnemyPawn = Controller->GetPawn();
	if (IsValid(EnemyPawn) == false)
	{
		return EBTNodeResult::Failed;
	}

	FVector AimLocation = EnemyPawn->GetActorLocation() + EnemyPawn->GetActorForwardVector() * 100.0f;
	Controller->ActivateAbility(AimLocation);

	return EBTNodeResult::Succeeded;
}
