// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretBase.h"
#include "TurretCannon.generated.h"

class AEnemyPawn;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATurretCannon : public ATurretBase
{
	GENERATED_BODY()

public:
	ATurretCannon();

	virtual void Tick(float DeltaTime) override;

protected:

	// Targeting and Firing
	AEnemyPawn* CurrentTarget = nullptr;

	void StartFireTimer();
	void StopFireTimer();
	
	void Fire();

	FTimerHandle FireTimer;

	void SelectTarget();
	void ResetTarget();

	void RotateTurret(float DeltaTime);

	float RotationSpeed = 10.f;

	virtual void OnEnemyEnterRange(AEnemyPawn* Enemy) override;
	
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* TurretParent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* TurretCannonParent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretCannonMesh;
	
};
