// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameState.h"

#include "TowerDefense/GameModes/RunGameMode.h"

void ARunGameState::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ARunGameState::beginplay"));

	GameMode = Cast<ARunGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		if (GameMode->IsLevelLoaded())
		{
			OnGameReady();
		}
		else
		{
			GameMode->OnGameReady.AddDynamic(this, &ARunGameState::OnGameReady);
		}
	}
}

void ARunGameState::TimerTick()
{
	PhaseRemainingTime--;

	UE_LOG(LogTemp, Warning, TEXT("A second %d"), PhaseRemainingTime);

	if (PhaseRemainingTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void ARunGameState::OnGameReady()
{
	UE_LOG(LogTemp, Warning, TEXT("ARunGameState::OnGameReady"));

	PhaseRemainingTime = 5;

	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ARunGameState::TimerTick,
		1.0f,
		true
	);

	OnPhaseStart.Broadcast();
}
