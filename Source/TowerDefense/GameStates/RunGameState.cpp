// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameState.h"

#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/PlayerControllers/RunPlayerController.h"
#include "TowerDefense/UI/RunHUD.h"

void ARunGameState::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ARunGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		if (GameMode->IsLevelLoaded())
		{
			OnLevelReady();
		}
		else
		{
			GameMode->OnLevelReady.AddDynamic(this, &ARunGameState::OnLevelReady);
		}
	}

	PlayerController = Cast<ARunPlayerController>(GetWorld()->GetFirstPlayerController());

	if (PlayerController)
	{
		HUD = Cast<ARunHUD>(PlayerController->GetHUD());
	}
}

void ARunGameState::TimerTick()
{
	PhaseRemainingTime--;

	UE_LOG(LogTemp, Warning, TEXT("A second %d"), PhaseRemainingTime);
	if (HUD)
	{
		HUD->UpdateNextWaveTimer(PhaseRemainingTime);
	}

	if (PhaseRemainingTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void ARunGameState::OnLevelReady()
{

	if (!GameMode)
	{
		return;
	}
	
	// Setup player
	PlayerHealth = GameMode->PlayerMaxHealth;
	PlayerCoins = GameMode->PlayerInitialCoins;


	PhaseRemainingTime = WaveNumber == 0 ? GameMode->FirstSetupPhaseTimer : GameMode->SetupPhaseTimer;

	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ARunGameState::TimerTick,
		1.0f,
		true
	);

	OnPhaseStart.Broadcast();
}
