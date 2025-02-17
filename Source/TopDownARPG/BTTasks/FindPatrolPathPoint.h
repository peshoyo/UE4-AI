// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FindPatrolPathPoint.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API UFindPatrolPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UFindPatrolPathPoint(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8 * node_memory) override;
};
