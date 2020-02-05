// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	AEnemyAIController();
	virtual void OnPossess(APawn* InPawn) override;


	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviourTreeComponent;

	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviourTree;

public:
	//AEnemyAIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

	//void BeginPlay() override;

	class UBlackboardComponent* getBlackboard() const;

	void ActivateAbility(FVector AimLocation);
};
