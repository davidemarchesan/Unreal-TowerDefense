// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;

UCLASS()
class TOWERDEFENSE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:

	AEnemyPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
