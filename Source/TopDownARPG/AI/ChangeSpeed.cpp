// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeSpeed.h"
#include "Characters/Guard.h"
#include "Controllers/Guard_AIController.h"

#include "GameFramework/CharacterMovementComponent.h"
UChangeSpeed::UChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent & OwnerComponent, uint8 * NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComponent, NodeMemory);
	//auto const Controller = Cast<AGuard_AIController>(OwnerComponent.GetAIOwner());
	auto const Controller = OwnerComponent.GetAIOwner();
	AGuard* Guard = Cast<AGuard>(Controller->GetPawn());

	Guard->GetCharacterMovement()->MaxWalkSpeed = Speed;

}

FString UChangeSpeed::GetStaticServiceDiscription() const
{
	return FString("Change Guard speed.");
}
