// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"

#include "TowerDefense/LayoutGrid.h"
#include "TowerDefense/PlayerControllers/RunPlayerController.h"
#include "TowerDefense/GameStates/RunGameState.h"
#include "TowerDefense/Turrets/TurretBase.h"

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

void ARunGameMode::RequestToggleBuildWallMode()
{
	if (GameState && GameState->GetPhase() == ERunPhase::Setup)
	{
		GameState->ToggleBuildWallMode();

		if (GameState->IsBuildWallMode() == false && Grid)
		{
			Grid->RequestResetPreviewWall();
		}
	}
}

bool ARunGameMode::CanBuildWall()
{
	return GameState && GameState->GetPhase() == ERunPhase::Setup && GameState->IsBuildWallMode();
}

void ARunGameMode::RequestWallPreview(FVector Location)
{
	if (Grid)
	{
		Grid->RequestPreviewWall(Location);
	}
}

void ARunGameMode::RequestResetPreviewWall()
{
	if (Grid)
	{
		Grid->RequestResetPreviewWall();
	}
}

void ARunGameMode::RequestWallBuild(FVector Location)
{
	if (GameState && GameState->GetPhase() == ERunPhase::Setup && GameState->IsBuildWallMode() && Grid)
	{
		Grid->RequestWallBuild(Location);
	}
}

void ARunGameMode::RequestWallRemoval(int32 Col, int32 Row)
{
	if (GameState && GameState->GetPhase() == ERunPhase::Setup && GameState->IsBuildWallMode() && Grid)
	{
		Grid->RequestWallRemoval(Col, Row);
	}
}

void ARunGameMode::RequestToggleBuildTurretMode()
{
	if (GameState && GameState->GetPhase() == ERunPhase::Setup)
	{
		GameState->ToggleBuildTurretMode();

		if (GameState->IsBuildTurretMode() == false && Grid)
		{
			Grid->RequestResetPreviewWall();
		}
	}
}

void ARunGameMode::RequestTurretPreview(FVector Location)
{
	if (Grid)
	{
		Grid->RequestPreviewTurret(Location);
	}
}

void ARunGameMode::RequestResetPreviewTurret()
{
	if (Grid)
	{
		Grid->RequestResetPreviewTurret();
	}
}

void ARunGameMode::RequestTurretBuild(const FVector& Location)
{
	if (GameState && GameState->IsBuildTurretMode() && Grid)
	{
		Grid->RequestTurretBuild(Location);
	}
}
