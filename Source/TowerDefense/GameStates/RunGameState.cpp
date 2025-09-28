// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameState.h"

#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/PlayerControllers/RunPlayerController.h"
#include "TowerDefense/UI/RunHUD.h"
#include "TowerDefense/Enums/RunPhase.h"

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

	OnTimerUpdate.Broadcast(PhaseRemainingTime);

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

	StartTimer(WaveNumber == 0 ? GameMode->FirstSetupPhaseTimer : GameMode->SetupPhaseTimer);

	OnPhaseStart.Broadcast(Phase);
}

void ARunGameState::GoToNextPhase()
{

	if (!GameMode)
	{
		return;
	}

	if (Phase == ERunPhase::Setup)
	{
		Phase = ERunPhase::Defense;
		GameMode->RequestResetPreviewWall();
		SetBuildWallMode(false);
	}
	else
	{
		Phase = ERunPhase::Setup;
		StartTimer(GameMode->SetupPhaseTimer);
	}

	OnPhaseStart.Broadcast(Phase);
	
}

void ARunGameState::StartTimer(int32 Seconds)
{

	PhaseRemainingTime = Seconds;
	
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ARunGameState::TimerTick,
		1.0f,
		true
	);
}

void ARunGameState::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ARunGameState::SetBuildWallMode(bool _bIsBuildWallMode)
{
	bIsBuildWallMode = _bIsBuildWallMode;

	if (bIsBuildWallMode == true)
	{
		SetBuildTurretMode(false);
	}
	
	OnBuildWallModeToggle.Broadcast(bIsBuildWallMode);
}

void ARunGameState::SetBuildTurretMode(bool _bIsBuildTurretMode)
{
	bIsBuildTurretMode = _bIsBuildTurretMode;

	if (bIsBuildTurretMode == true)
	{
		SetBuildWallMode(false);	
	}
	
	OnBuildTurretModeToggle.Broadcast(bIsBuildTurretMode);
}

void ARunGameState::ToggleBuildWallMode()
{
	SetBuildWallMode(!bIsBuildWallMode);
}

void ARunGameState::ToggleBuildTurretMode()
{
	SetBuildTurretMode(!bIsBuildTurretMode);
}

void ARunGameState::SkipSetupPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("ARunGameState::SkipSetupPhase"));

	StopTimer();

	GoToNextPhase();
}


