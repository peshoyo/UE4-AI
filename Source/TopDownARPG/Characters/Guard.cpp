// Fill out your copyright notice in the Description page of Project Settings.


#include "Guard.h"
#include "TopDownARPG.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameModes/TopDownARPGGameMode.h"

// Sets default values
AGuard::AGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	OnTakeAnyDamage.AddDynamic(this, &AGuard::TakeAnyDamage);
}

// Called when the game starts or when spawned
void AGuard::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInstanceDynamic* const MaterialInstance = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	if (MaterialInstance)
	{
		MaterialInstance->SetVectorParameterValue("BodyColor", FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		GetMesh()->SetMaterial(0, MaterialInstance);
	}

	FTopDownARPGCharacterStruct* CharacterStruct = CharacterStatsRow.GetRow<FTopDownARPGCharacterStruct>(TEXT(""));

	if (CharacterStruct == nullptr)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("ATopDownARPGCharacter::BeginPlay CharacterStruct != nullptr"));
		return;
	}

	Health = CharacterStruct->MaximumHealth;

	for (const TSubclassOf<UAbility>Template : CharacterStruct->AbilityTemplates)
	{
		AbilityInstances.Add(NewObject<UAbility>(this, Template));
	}
}

// Called every frame
void AGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AGuard::TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigateBy, AActor* DamageCauser)
{
	
	UE_LOG(LogTopDownARPG, Display, TEXT("AGuard::TakeAnyDamage current health = %f"), (Health - Damage));
	Health -= Damage;
	if (Health <= 0.0f)
	{
		Death();
		this->Destroy();
		UE_LOG(LogTopDownARPG, Display, TEXT("AGuard::Guard should be dead."));
	}
}
void AGuard::Death()
{
	
		UCharacterMovementComponent* Movement = GetCharacterMovement();
		Movement->MaxWalkSpeed = 0.0f;
		Movement->bOrientRotationToMovement = false;

}
APatrolPath* AGuard::GetPatrolPath()
{
	return PatrolPath;
}
// Called to bind functionality to input
void AGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AGuard::GetHealth() const
{
	return Health;
}


