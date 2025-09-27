// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"

#include "TowerDefense/LayoutGrid.h"
#include "TowerDefense/PlayerControllers/RunPlayerController.h"
#include "TowerDefense/GameStates/RunGameState.h"

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetGameComponents();

	LoadLevel();
}

void ARunGameMode::GetGameComponents()
{
	GameState = GetGameState<ARunGameState>();
	PlayerController = Cast<ARunPlayerController>(GetWorld()->GetFirstPlayerController());
}

void ARunGameMode::LoadLevel()
{
	// Spawn grid
	InitializeGrid();

	bIsLevelLoaded = true;
	OnLevelReady.Broadcast();
}

void ARunGameMode::InitializeGrid()
{
	if (!GridBlueprintClass)
	{
		return;
	}

	Grid = GetWorld()->SpawnActor<ALayoutGrid>(GridBlueprintClass, FVector::ZeroVector,
	                                           FRotator::ZeroRotator);

	if (Grid)
	{
		Grid->Initialize(GridCols, GridRows);
	}
}

FVector ARunGameMode::GetCameraStartLocation()
{
	if (Grid)
	{
		return Grid->GetWorldGridCenter();
	}

	return FVector::ZeroVector;
}
