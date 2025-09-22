// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"

class ALayoutGrid;

/**
 * This class defines the Run rules
 */
UCLASS()
class TOWERDEFENSE_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

private:

	// Grid
	void InitializeGrid();

public:
	
	// Stats
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float PlayerMaxHealth = 2000.f;
	
	// Phases
	UPROPERTY(EditDefaultsOnly, Category = "Phases")
	int32 BuyAndBuildPhaseTimer = 20;

	// Grid
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TSubclassOf<ALayoutGrid> GridBlueprintClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 GridCols = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 GridRows = 10;
	
};
