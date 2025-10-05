// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefense/Enums/RunPhase.h"
#include "EnemySpawner.generated.h"

class AEnemyPawn;
class ARunGameMode;

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
	void OnPhaseStart(ERunPhase NewPhase);

	ARunGameMode* GameMode;

	UDataTable* EnemyDataTable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnEnemy();

	FTimerHandle TimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="BluePrints")
	TSubclassOf<AEnemyPawn> EnemyBluePrintClass;

	void SetNexusLocation(FVector Location) { NexusLocation = Location; }
	
	FVector NexusLocation;
	
};
