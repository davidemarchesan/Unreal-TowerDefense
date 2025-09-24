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

	// Stampa la classe impostata come GameState
	if (GameStateClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode says GameStateClass = %s"),
			*GameStateClass->GetName());
	}

	// Stampa l'istanza effettiva di GameState in gioco
	if (GameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode has GameState instance = %s"),
			*GameState->GetClass()->GetName());
	}
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

	// Setup camera

	UE_LOG(LogTemp, Warning, TEXT("GAMEMODE: LEVEL LOADED"));
	bIsLevelLoaded = true;
	OnGameReady.Broadcast();
	
}

void ARunGameMode::InitializeGrid()
{
	if (!GridBlueprintClass)
	{
		return;
	}

	if (ALayoutGrid* Grid = GetWorld()->SpawnActor<ALayoutGrid>(GridBlueprintClass, FVector::ZeroVector,
	                                                            FRotator::ZeroRotator))
	{
		Grid->Initialize(GridCols, GridRows);
	}
}
