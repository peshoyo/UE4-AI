// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPathPoint.h"
#include "Controllers/Guard_AIController.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Guard.h"
 

UFindPatrolPathPoint::UFindPatrolPathPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Patrol Path");
}

EBTNodeResult::Type UFindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComponent, uint8 * node_memory)
{
	//Get controller for the patrolling Guard
	auto const Controller = Cast<AGuard_AIController>(OwnerComponent.GetAIOwner());

	//Get patrol path index
	int const index = Controller->GetBlackboard()->GetValueAsInt(bb_keys::patrol_path_index);

	//Use the index to get to current patrol path

	AGuard* const Guard = Cast<AGuard>(Controller->GetPawn());
	FVector const Point = Guard->GetPatrolPath()->GetPatrolPoints(index);

	//Transform point to global position
	FVector const GlobalPoint = Guard->GetPatrolPath()->GetActorTransform().TransformPosition(Point);

	//Write current global point to blackboard
	Controller->GetBlackboard()->SetValueAsVector(bb_keys::patrol_path_vector, GlobalPoint);
	 
	//Finish with success.
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
