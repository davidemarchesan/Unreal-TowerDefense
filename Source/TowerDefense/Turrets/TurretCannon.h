// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretBase.h"
#include "TurretCannon.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATurretCannon : public ATurretBase
{
	GENERATED_BODY()

public:
	ATurretCannon();

protected:
	
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
