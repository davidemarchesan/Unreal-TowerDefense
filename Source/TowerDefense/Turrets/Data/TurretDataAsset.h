// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDefense/Turrets/Data/TurretStats.h"
#include "TurretDataAsset.generated.h"

class ATurretBase;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTurretDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	FName TurretID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	TSubclassOf<ATurretBase> TurretClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	FTurretStats Stats;
	
};
