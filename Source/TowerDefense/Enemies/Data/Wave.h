#pragma once

#include "CoreMinimal.h"
#include "Wave.generated.h"

USTRUCT(BlueprintType)
struct FWaveEnemiesGroup
{

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SpawnDelay = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName EnemyId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Count;
		
};

USTRUCT(BlueprintType)
struct FWave
{

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SpawnDelay = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FWaveEnemiesGroup> EnemiesGroups;
	
};