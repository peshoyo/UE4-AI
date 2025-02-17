// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOPDOWNARPG_API UFindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UFindRandomLocation(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* node_memory);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess = "True"))
		float SearchRadius = 1500.0f;
};
