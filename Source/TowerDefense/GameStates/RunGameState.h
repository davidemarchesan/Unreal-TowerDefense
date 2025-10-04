// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TowerDefense/Enums/RunPhase.h"
#include "RunGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseStart, ERunPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdate, int32, Time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildWallModeToggle, bool, bIsBuildWallMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildTurretModeToggle, bool, bIsBuildTurretMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHealthChange, float, PlayerHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCoinsChange, float, PlayerCoins);

class ARunGameMode;
class ARunPlayerController;
class ARunHUD;

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

	ARunGameMode* GameMode;
	ARunPlayerController* PlayerController;
	ARunHUD* HUD;

	ERunPhase Phase = ERunPhase::Setup;

	int32 PhaseRemainingTime;
	FTimerHandle TimerHandle;

	void TimerTick();

	UFUNCTION()
	void OnLevelReady();

	void GoToNextPhase();

	void StartTimer(int32 Seconds);

	void StopTimer();

	int32 WaveNumber = 0;

	// Stats
	void SetPlayerHealth(float _PlayerHealth);
	float PlayerHealth;
	
	void SetPlayerCoins(float _PlayerCoins);
	float PlayerCoins;

	// Build Wall Mode
	bool bIsBuildWallMode = false;
	void SetBuildWallMode(bool _bIsBuildWallMode);

	// Build Wall Mode
	bool bIsBuildTurretMode = false;
	void SetBuildTurretMode(bool _bIsBuildTurretMode);

public:

	// Build Wall Mode
	void ToggleBuildWallMode();
	bool IsBuildWallMode() const { return bIsBuildWallMode; }

	FOnBuildWallModeToggle OnBuildWallModeToggle;

	// Build Turret Mod
	void ToggleBuildTurretMode();
	bool IsBuildTurretMode() const { return bIsBuildTurretMode; }

	FOnBuildTurretModeToggle OnBuildTurretModeToggle;

	// Phase
	ERunPhase GetPhase() const { return Phase; }

	FOnPhaseStart OnPhaseStart;

	FOnTimerUpdate OnTimerUpdate;

	void SkipSetupPhase();

	// Stats
	float GetPlayerHealth() const { return PlayerHealth; }
	FOnPlayerHealthChange OnPlayerHealthChange;

	float GetPlayerCoins() const { return PlayerCoins; }
	FOnPlayerCoinsChange OnPlayerCoinsChange;
	
};
