// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretDataAsset.h"
#include "Engine/DataAsset.h"
#include "TurretRegistry.generated.h"

class UTurretDataAsset;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTurretRegistry : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	TArray<UTurretDataAsset*> Turrets;

	UTurretDataAsset* GetTurretByID(FName TurretID) const
	{
		for (auto* Turret : Turrets)
		{
			if (Turret && Turret->TurretID == TurretID)
			{
				return Turret;
			}
		}
		return nullptr;
	}
	
};
