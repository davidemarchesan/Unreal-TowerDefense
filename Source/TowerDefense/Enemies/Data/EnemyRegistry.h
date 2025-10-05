// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDefense/Enemies/EnemyPawn.h"
#include "EnemyRegistry.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEnemyRegistry : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	TMap<FName, TSubclassOf<AEnemyPawn>> Enemies;

	TSubclassOf<AEnemyPawn> GetEnemyClass(FName EnemyID) const
	{
		if (const TSubclassOf<AEnemyPawn>* Found = Enemies.Find(EnemyID))
		{
			return *Found;
		}
		return nullptr;
	}
	
};
