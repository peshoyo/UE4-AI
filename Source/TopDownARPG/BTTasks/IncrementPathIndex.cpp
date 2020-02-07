	// Fill out your copyright notice in the Description page of Project Settings.


#include "IncrementPathIndex.h"
#include "Controllers/Guard_AIController.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Guard.h"
#include <cmath>

UIncrementPathIndex::UIncrementPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent & OwnerComponent, uint8 * node_memory)
{
	auto const Controller = Cast<AGuard_AIController>(OwnerComponent.GetAIOwner());
	AGuard* const Guard = Cast<AGuard>(Controller->GetPawn());
	int const NumOfPoints = Guard->GetPatrolPath()->num();
	int const MinIndex = 0;
	int const MaxIndex = NumOfPoints - 1;

	//Get and set blackboard index
	int Index = Controller->GetBlackboard()->GetValueAsInt(bb_keys::patrol_path_index);
	if (Bidirectional)
	{
		if (Index >= MaxIndex && Direction == EDirectionType::Forward)
		{
			Direction = EDirectionType::Reverse;
		}
		else if (Index == MinIndex && Direction == EDirectionType::Reverse)
		{
			Direction = EDirectionType::Forward;
		}
		Controller->GetBlackboard()->SetValueAsInt(bb_keys::patrol_path_index, (Direction == EDirectionType::Forward ? ++Index : --Index) % NumOfPoints);
	}
	else
	{
		if (Index >= MaxIndex)Index = 0;
		else ++Index;
		Controller->GetBlackboard()->SetValueAsInt(bb_keys::patrol_path_index, Index);
	}

	

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
