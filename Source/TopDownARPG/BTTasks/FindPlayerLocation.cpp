 // Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "TopDownARPG/Controllers/Guard_AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BlackBoardKeys.h"


UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& ObjectInitializer) 
{
	NodeName = TEXT("FindPlayerLocation");

}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComponent, uint8 * node_memory)
{
	//Get player character and guard controller.
	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const Controller = Cast<AGuard_AIController>(OwnerComponent.GetAIOwner());


	FVector const PlayerLocation = Player->GetActorLocation();
	if (SearchRandom)
	{
		FNavLocation Location;
		//Generate random location near the player
		UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (NavigationSystem->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Location, nullptr))
		{
			Controller->GetBlackboard()->SetValueAsVector(bb_keys::target_location, Location.Location);
		}
	}
	else
	{
		Controller->GetBlackboard()->SetValueAsVector(bb_keys::target_location, PlayerLocation);
	}

	//Exit with success.
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
