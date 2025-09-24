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

	// HUD
	void InitializeOverlays();



	bool bShowLoadingScreen = true;

	bool bIsBuildMode = false;

	// Delegates
	void InitializeDelegateSubscribers();
	
	UFUNCTION()
	void OnGameReady();

	UFUNCTION()
	void OnPhaseStart();

	// HUD Components
	TSharedPtr<SBorder> LoadingScreen;
	
	TSharedPtr<SBorder> BuildModeBorder;

	TSharedPtr<SBox> StandardModeBox;
	TSharedPtr<SBox> BuildModeBox;
	
	TSharedPtr<SBox> SaveLayoutBox;

	// Button callbacks
	FReply OnToggleBuildMode();

	FReply OnSaveLayout();

	void UpdateComponentsOnBuildMode();
};
