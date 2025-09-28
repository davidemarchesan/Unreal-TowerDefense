// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"

class ALayoutGrid;
class ARunPlayerController;
class ARunGameState;
class ATurretBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelReady); // Fired when Level is ready to be played

/**
 * This class defines the Run rules
 */
UCLASS()
class TOWERDEFENSE_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Getters
	bool IsLevelLoaded() const { return bIsLevelLoaded; }

	// Delegates
	FOnLevelReady OnLevelReady;

private:
	ARunPlayerController* PlayerController;

	ARunGameState* GameState;

	void GetGameComponents();

	void LoadLevel();

	bool bIsLevelLoaded = false;

	// Grid
	ALayoutGrid* Grid;
	
	void InitializeGrid();

public:
	// Stats
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float PlayerMaxHealth = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float PlayerInitialCoins = 2000.f;

	// Phases
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int32 FirstSetupPhaseTimer = 60;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int32 SetupPhaseTimer = 20;

	// Grid
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TSubclassOf<ALayoutGrid> GridBlueprintClass;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 GridCols = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 GridRows = 10;

	FVector GetCameraStartLocation();

	// Build Wall Mode
	void RequestToggleBuildWallMode();

	bool CanBuildWall();

	void RequestWallPreview(FVector Location);

	void RequestResetPreviewWall();

	void RequestWallBuild(FVector Location);
	
	void RequestWallRemoval(int32 Col, int32 Row);

	// Build Turret Mode
	void RequestToggleBuildTurretMode();

	void RequestTurretBuild(const FVector& Location);

	UPROPERTY(EditAnywhere, Category = "BluePrints")
	TSubclassOf<ATurretBase> TurretBluePrintClass;
};
