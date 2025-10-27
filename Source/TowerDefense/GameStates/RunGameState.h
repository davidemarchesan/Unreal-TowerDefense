// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TowerDefense/Enemies/Data/EnemyRegistry.h"
#include "TowerDefense/Enemies/Data/Wave.h"
#include "TowerDefense/Enums/RunPhase.h"
#include "TowerDefense/GameModes/Data/RunGameModeMetas.h"
#include "TowerDefense/Turrets/Data/TurretRegistry.h"
#include "RunGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseStart, ERunPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDefensePhaseStart, FWave, Wave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdate, int32, Time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildWallModeToggle, bool, bIsBuildWallMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildTurretModeToggle, bool, bIsBuildTurretMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHealthChange, float, PlayerHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCoinsChange, float, PlayerCoins);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerPointsChange, float, PlayerPoints);

class ARunGameMode;
class ARunPlayerController;
class ARunHUD;
class AEnemyPawn;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ARunGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
	
private:

	void TimerTick();

	ARunPlayerController* PlayerController;
	ARunHUD* HUD;

	UFUNCTION()
	void OnLevelReady();

	// Game phase
	ERunPhase Phase = ERunPhase::Setup;

	// Game phase - Setup phase timer
	int32 SetupPhaseRemainingTime;
	FTimerHandle SetupPhaseTimerHandle;

	void StartSetupPhaseTimer(int32 Seconds);
	void StopSetupPhaseTimer();

	// Game phase - Defense phase
	int32 WaveNumber = 0;

	int32 EnemiesAlive = 0;
	
	UFUNCTION()
	void OnAnyEnemyDeath(AEnemyPawn* Enemy);

	// Player stats
	void SetPlayerHealth(float _PlayerHealth);
	float PlayerHealth;
	
	void SetPlayerCoins(float _PlayerCoins);
	float PlayerCoins;

	float PlayerPoints = 0.f;
	
	// Build mode
	bool bIsBuildingMode = false;

	// Build Wall Mode
	bool bIsBuildWallMode = false;
	void SetBuildWallMode(bool _bIsBuildWallMode);

	// Build Wall Mode
	bool bIsBuildTurretMode = false;
	void SetBuildTurretMode(bool _bIsBuildTurretMode);

	// Game camera
	FVector CameraStartLocation;

	// Turrets data
	UTurretRegistry* TurretRegistry;
	UDataTable* TurretDataTable;

	// Enemies data
	UEnemyRegistry* EnemyRegistry;
	UDataTable* EnemyDataTable;

	// Game mode metas
	FRunGameModeMetas* GameModeMetas;

public:

	// Turrets data
	void SetTurretData(UTurretRegistry* InTurretRegistry, UDataTable* InTurretDataTable) { TurretRegistry = InTurretRegistry; TurretDataTable = InTurretDataTable; }
	UDataTable* GetTurretDataTable() { return TurretDataTable; }
	
	// Enemies data
	void SetEnemyData(UEnemyRegistry* InEnemyRegistry, UDataTable* InEnemyDataTable) { EnemyRegistry = InEnemyRegistry; EnemyDataTable = InEnemyDataTable; }
	UDataTable* GetEnemyDataTable() { return EnemyDataTable; }
	
	// Game mode metas
	void SetGameModeMetas(FRunGameModeMetas* InGameModeMetas) { GameModeMetas = InGameModeMetas; }
	FRunGameModeMetas* GetGameModeMetas() const { return GameModeMetas; }

	// Build mode
	bool IsBuildingMode() const { return bIsBuildingMode; }

	// Build Wall Mode
	void ToggleBuildWallMode();
	bool IsBuildWallMode() const { return bIsBuildWallMode; }

	FOnBuildWallModeToggle OnBuildWallModeToggle;

	// Build Turret Mode
	void ToggleBuildTurretMode();
	bool IsBuildTurretMode() const { return bIsBuildTurretMode; }

	FOnBuildTurretModeToggle OnBuildTurretModeToggle;

	// Game camera
	FVector GetCameraStartLocation() { return CameraStartLocation; }
	void SetCameraStartLocation(FVector InLocation) { CameraStartLocation = InLocation; }

	// Game phase
	ERunPhase GetPhase() const { return Phase; }

	FOnPhaseStart OnPhaseStart;
	FOnDefensePhaseStart OnDefensePhaseStart;

	FOnTimerUpdate OnTimerUpdate;

	void GoToNextPhase();
	void SkipSetupPhase();
	
	// Player stats - Health
	float GetPlayerHealth() const { return PlayerHealth; }
	FOnPlayerHealthChange OnPlayerHealthChange;
	
	void ReducePlayerHealth(float Damage);

	// Player stats - Coins
	float GetPlayerCoins() const { return PlayerCoins; }
	FOnPlayerCoinsChange OnPlayerCoinsChange;

	void AddPlayerCoins(float _PlayerCoins);
	
	void SpendPlayerCoins(float _PlayerCoins);

	// Player stats - Points
	float GetPlayerPoints() const { return PlayerPoints; }
	FOnPlayerPointsChange OnPlayerPointsChange;
	
	void AddPlayerPoints(float _PlayerPoints);
	
};
