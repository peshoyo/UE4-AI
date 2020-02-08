// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "UpdateHealthPercentage.h"
#include "Controllers/Guard_AIController.h"
#include "BlackBoardKeys.h" 
#include "Characters/Guard.h"


UUpdateHealthPercentage::UUpdateHealthPercentage()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Update Health");
}
void UUpdateHealthPercentage::OnBecomeRelevant(UBehaviorTreeComponent & OwnerComponent, uint8 * NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComponent, NodeMemory);

	auto const Controller = Cast<AGuard_AIController>(OwnerComponent.GetAIOwner());

	AGuard* PlayerCharacter = Cast<AGuard>(Controller->GetPawn());
	float MaxHealth = PlayerCharacter->MaxHealth;
	float CurrentHealth = PlayerCharacter->GetHealth();
	float Percentage = (CurrentHealth / MaxHealth) * 100;
	Controller->GetBlackboard()->SetValueAsFloat(bb_keys::health_percentage, Percentage);
	

}

FString UUpdateHealthPercentage::GetStaticServiceDiscription() const
{
	return FString("Update Health Percentage");
}
