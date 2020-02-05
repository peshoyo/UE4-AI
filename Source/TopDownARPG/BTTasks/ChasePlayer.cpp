// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"
#include "TopDownARPG/Controllers/Guard_AIController.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UChasePlayer::UChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComponent, uint8 * node_memory)
{
	auto const Controller = Cast<AGuard_AIController>(OwnerComponent.GetAIOwner());
	FVector const PlayerLocation = Controller->GetBlackboard()->GetValueAsVector(bb_keys::target_location);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
