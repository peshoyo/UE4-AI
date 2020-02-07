// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Abilities/Ability.h"
#include "AI/PatrolPath.h"
#include "DataTables/TopDownARPGCharacterStruct.h"
#include "Guard.generated.h"

UCLASS()
class TOPDOWNARPG_API AGuard : public ACharacter
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	AGuard();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "GuardHealth")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "GuardHealth")
	float Health;

	UFUNCTION(BlueprintPure, Category = "GuardHealth")
	float GetHealth()const;

	UFUNCTION()
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigateBy, AActor* DamageCauser);

	void Death();

	UPROPERTY()
	TArray<UAbility*> AbilityInstances;

	APatrolPath* GetPatrolPath();
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		APatrolPath* PatrolPath;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<UAbility>> AbilityTemplates;

	UPROPERTY(EditAnywhere)
		FDataTableRowHandle CharacterStatsRow;
};
