// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, AEnemyPawn*, Enemy);

UCLASS()
class TOWERDEFENSE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:

	AEnemyPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float Health;

	void SetDestination(FVector Location);

	// Damage
	void ApplyDamage(float Damage);

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnEnemyDeath OnEnemyDeath;

protected:

	virtual void BeginPlay() override;

private:

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UFloatingPawnMovement* MovementComponent;


};
