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

void ARunGameState::OnGameReady()
{
	UE_LOG(LogTemp, Warning, TEXT("ARunGameState::OnGameReady"));

	OnPhaseStart.Broadcast();
}
