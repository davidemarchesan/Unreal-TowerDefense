// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TurretRegistry.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTurretRegistry : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	TMap<FName, TSubclassOf<ATurretBase>> Turrets;

	TSubclassOf<ATurretBase> GetTurretClass(FName TurretID) const
	{
		if (const TSubclassOf<ATurretBase>* Found = Turrets.Find(TurretID))
		{
			return *Found;
		}
		return nullptr;
	}
	
};
