// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "TopDownARPG/Controllers/Guard_AIController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoardKeys.h" 

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComponent, uint8 * node_memory)
{
	//Get GuardAIController and its Guard
	auto const GuardController = Cast<AGuard_AIController>(OwnerComponent.GetAIOwner());
	auto const Guard = GuardController->GetPawn();

	//Find guard location to use as an origin location.
	FVector const GuardOrigin = Guard->GetActorLocation();
	FNavLocation RandomLocation;

	//Generate random location using navigation system.
	UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavigationSystem->GetRandomPointInNavigableRadius(GuardOrigin, SearchRadius, RandomLocation, nullptr))
	{
		GuardController->GetBlackboard()->SetValueAsVector(bb_keys::target_location, RandomLocation.Location);
	}

	//Finish with success.
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
