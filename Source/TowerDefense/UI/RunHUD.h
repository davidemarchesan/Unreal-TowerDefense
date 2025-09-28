// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RunHUD.generated.h"

class ARunGameMode;
class ARunGameState;
class ARunPlayerController;

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
	ARunGameState* GameSate;
	ARunPlayerController* PlayerController;

	// Utils
	

	// HUD
	void InitializeOverlays();

	void CreateTopBarOverlay(const TSharedRef<SOverlay>& RootOverlay);
	
	bool bShowLoadingScreen = true;

	bool bIsBuildMode = false;

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

	// HUD Components
	TSharedPtr<SBorder> LoadingScreen;

	TSharedPtr<SHorizontalBox> NextWaveHBox;
	TSharedPtr<STextBlock> NextWaveTimerTextBlock;
	TSharedPtr<SButton> NextWaveSkipButton;
	
	TSharedPtr<SBorder> BuildModeBorder; // deprecated

	TSharedPtr<SBox> StandardModeBox; // deprecated
	TSharedPtr<SBox> BuildModeBox; // deprecated
	
	TSharedPtr<SBox> SaveLayoutBox; // deprecated

	// Button callbacks
	FReply OnSkipSetupPhase();
};
