// Fill out your copyright notice in the Description page of Project Settings.


#include "Guard_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TopDownARPG/Characters/TopDownARPGCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "BlackBoardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"


AGuard_AIController::AGuard_AIController(FObjectInitializer const& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/TopDownCPP/Blueprints/Guards/Guard_BT.Guard_BT'"));
	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	} 
	BehaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	Blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	SetupPerceptionSystem();
}

void AGuard_AIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void AGuard_AIController::OnPossess(APawn * const InPawn)
{
	Super::OnPossess(InPawn);
	if (Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent * AGuard_AIController::GetBlackboard() const
{
	return Blackboard;
}



void AGuard_AIController::OnTargetDetected(AActor * actor, FAIStimulus const stimulus)
{
	if (auto const ch = Cast<ATopDownARPGCharacter>(actor))
	{
		GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

void AGuard_AIController::SetupPerceptionSystem()
{
	//Create and initialise sight configuration object
	Sight_Config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	Sight_Config->SightRadius = 500.0f;
	Sight_Config->LoseSightRadius = Sight_Config->SightRadius + 50.0f;
	Sight_Config->PeripheralVisionAngleDegrees = 90.0f;
	Sight_Config->SetMaxAge(5.0f);
	Sight_Config->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	Sight_Config->DetectionByAffiliation.bDetectEnemies = true;
	Sight_Config->DetectionByAffiliation.bDetectFriendlies = true;
	Sight_Config->DetectionByAffiliation.bDetectNeutrals = true;

	//Add sight config comp to perception comp
	GetPerceptionComponent()->SetDominantSense(*Sight_Config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AGuard_AIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*Sight_Config);
}
