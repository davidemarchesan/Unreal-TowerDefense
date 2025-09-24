// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TowerDefense/Enums/RunPhase.h"
#include "RunGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhaseStart);

class ARunGameMode;

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

	ERunPhase Phase = ERunPhase::Build;

	int32 PhaseRemainingTime;
	FTimerHandle TimerHandle;

	void TimerTick();

	UFUNCTION()
	void OnGameReady();

	int32 WaveNumber = 0;

	float PlayerHealth;

	float PlayerCoins;

public:

	FOnPhaseStart OnPhaseStart;
	
};
