// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API UChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UChangeSpeed();

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8 * NodeMemory) override;

protected:
	FString GetStaticServiceDiscription() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float Speed = 600.0f;
};
