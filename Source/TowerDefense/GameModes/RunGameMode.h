// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/RunGameModeMetas.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefense/Enemies/Data/EnemyRegistry.h"
#include "TowerDefense/Enemies/Data/EnemyStats.h"
#include "TowerDefense/Turrets/Data/TurretStats.h"
#include "RunGameMode.generated.h"

class ALayoutGrid;
class AEnemySpawner;
class ANexus;
class ARunPlayerController;
class ARunGameState;
class ATurretBase;
class UTurretRegistry;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelReady); // Fired when Level is ready to be played

/**
 * This class defines the Run rules
 */
UCLASS()
class TOWERDEFENSE_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Registry")
	UDataTable* GameModeMetasTable;

	UPROPERTY(EditDefaultsOnly, Category = "Registry")
	UTurretRegistry* TurretRegistry;

	UPROPERTY(EditDefaultsOnly, Category = "Registry")
	UDataTable* TurretDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Registry")
	UEnemyRegistry* EnemyRegistry;

	UPROPERTY(EditDefaultsOnly, Category = "Registry")
	UDataTable* EnemyDataTable;

	// Getters
	bool IsLevelLoaded() const { return bIsLevelLoaded; }

	// Delegates
	FOnLevelReady OnLevelReady;

private:
	ARunPlayerController* PlayerController;

	ARunGameState* GameState;

	void LoadGameModeMetas();

	void GetGameComponents();

	void LoadLevel();

	bool bIsLevelLoaded = false;

	// Grid
	ALayoutGrid* Grid;
	
	void InitializeGrid();

	// Enemy spawner
	AEnemySpawner* EnemySpawner;

public:
	// Stats
	FRunGameModeMetas* GameModeMetas;

	FTurretStats* GetTurretStats(FName TurretID);

	// Enemies
	UDataTable* GetEnemyDataTable() const { return EnemyDataTable; }
	
	FEnemyStats* GetEnemyStats(FName EnemyID);

	// Phases
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int32 FirstSetupPhaseTimer = 60;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int32 SetupPhaseTimer = 20;

	// Grid
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TSubclassOf<ALayoutGrid> GridBlueprintClass;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TSubclassOf<AEnemySpawner> EnemySpawnerBlueprintClass;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TSubclassOf<ANexus> NexusBlueprintClass;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 GridCols = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 GridRows = 10;

	FVector GetCameraStartLocation();

	// Build Wall Mode
	void RequestToggleBuildWallMode();

	bool CanBuildWall();

	void RequestWallPreview(FVector Location);

	void RequestResetPreviewWall();

	void RequestWallBuild(FVector Location);
	
	void RequestWallRemoval(int32 Col, int32 Row);

	// Build Turret Mode
	void RequestToggleBuildTurretMode(FName& TurretID);

	void RequestTurretPreview(FName TurretID, FVector Location);

	void RequestResetPreviewTurret();

	void RequestTurretBuild(FName TurretID, const FVector& Location);

	// void RequestTurretRemoval(int32 Col, int32 Row);

	UPROPERTY(EditAnywhere, Category = "BluePrints")
	TSubclassOf<ATurretBase> TurretBluePrintClass;
};
