// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Wave.h"
#include "GameFramework/Actor.h"
#include "TowerDefense/Enums/RunPhase.h"
#include "EnemySpawner.generated.h"

class AEnemyPawn;
class ARunGameMode;
class ARunGameState;

UCLASS()
class TOWERDEFENSE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

private:

	ERunPhase Phase = ERunPhase::Setup;

	UFUNCTION()
	void OnDefensePhaseStart(FWave Wave);

	ARunGameMode* GameMode;

	ARunGameState* GameState;

	UDataTable* EnemyDataTable;

	// Wave
	FWave HardCodedWave;
	
	FTimerHandle EnemiesGroupSpawnTimerHandle;
	FTimerHandle EnemyUnitSpawnTimerHandle;

	void StartWave();
	void StartEnemiesGroup();

	void GoToNextEnemiesGroup();

	int32 CurrentEnemyGroup = 0;
	int32 CurrentEnemyUnit = 0;

	void SpawnEnemy();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="BluePrints")
	TSubclassOf<AEnemyPawn> EnemyBluePrintClass;

	void SetNexusLocation(FVector Location) { NexusLocation = Location; }
	
	FVector NexusLocation;
	
};
