// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Data/EnemyStats.h"
#include "EnemyPawn.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;
class ARunGameMode;
class ARunGameState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, AEnemyPawn*, Enemy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyEnemyDeath, AEnemyPawn*, Enemy);

UCLASS()
class TOWERDEFENSE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:

	AEnemyPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Turret")
	FName EnemyID;

	void SetDestination(FVector Location);

	float Health;

	// Damage
	void ApplyDamage(float Damage);

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnEnemyDeath OnEnemyDeath;

	void Die();
	static FOnAnyEnemyDeath OnAnyEnemyDeath;

	// Stats
	FEnemyStats* Stats;

protected:

	virtual void BeginPlay() override;

	ARunGameMode* GameMode;

	ARunGameState* GameState;

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* HealthBarComponent;


};
