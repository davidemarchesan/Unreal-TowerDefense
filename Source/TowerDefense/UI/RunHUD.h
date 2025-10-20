// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RunHUD.generated.h"

class ARunGameMode;
class ARunGameState;
class ARunPlayerController;
class STopBarStat;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ARunHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	void ToggleBuildMode(bool _bIsBuildMode);

private:

	ARunGameMode* GameMode;
	ARunGameState* GameState;
	ARunPlayerController* PlayerController;

	// Utils
	

	// HUD
	void InitializeOverlays();

	void CreateTopBarOverlay(const TSharedRef<SOverlay>& RootOverlay);
	void CreateBottomBarOverlay(const TSharedRef<SOverlay>& RootOverlay);
	
	bool bShowLoadingScreen = true;

	bool bIsBuildMode = false;

	void InitializeHUDVariables();

	// Delegates
	void InitializeDelegateSubscribers();
	
	UFUNCTION()
	void OnLevelReady();

	UFUNCTION()
	void OnPhaseStart(ERunPhase NewPhase);

	void PrepareForSetupPhase();
	
	void PrepareForDefensePhase();

	UFUNCTION()
	void OnTimerUpdate(int32 Time);

	UFUNCTION()
	void OnPlayerHealthChange(float PlayerHealth);

	UFUNCTION()
	void OnPlayerCoinsChange(float PlayerCoins);

	UFUNCTION()
	void OnPlayerPointsChange(float PlayerPoints);

	// HUD Components
	TSharedPtr<SBorder> LoadingScreen;

	TSharedPtr<SHorizontalBox> NextWaveHBox;
	TSharedPtr<STextBlock> NextWaveTimerTextBlock;
	TSharedPtr<SButton> NextWaveSkipButton;

	TSharedPtr<SHorizontalBox> BottomBar;

	TSharedPtr<STopBarStat> PlayerHealthStat;
	TSharedPtr<STopBarStat> PlayerCoinsStat;
	TSharedPtr<STopBarStat> PlayerPointsStat;
	
	TSharedPtr<SBorder> BuildModeBorder; // deprecated

	TSharedPtr<SBox> StandardModeBox; // deprecated
	TSharedPtr<SBox> BuildModeBox; // deprecated
	
	TSharedPtr<SBox> SaveLayoutBox; // deprecated

	// Button callbacks
	FReply OnSkipSetupPhase();
};
