// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Guard_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API AGuard_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AGuard_AIController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());


	void BeginPlay() override;
	void OnPossess(APawn* const InPawn) override;

	class UBlackboardComponent* GetBlackboard() const;

	void ActivateAbility(FVector AimLocation, int index);

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* Blackboard;

	class UAISenseConfig_Sight* Sight_Config;

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

	void SetupPerceptionSystem();
};
