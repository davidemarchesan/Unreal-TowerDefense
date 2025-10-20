// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"

#include "TowerDefense/LayoutGrid.h"
#include "TowerDefense/Enemies/EnemySpawner.h"
#include "TowerDefense/PlayerControllers/RunPlayerController.h"
#include "TowerDefense/GameStates/RunGameState.h"
#include "TowerDefense/Nexus/Nexus.h"
#include "TowerDefense/Turrets/TurretBase.h"
#include "TowerDefense/Turrets/Data/TurretRegistry.h"

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	LoadGameModeMetas();

	GetGameComponents();

	LoadLevel();
}

void ARunGameMode::LoadGameModeMetas()
{
	if (GameModeMetasTable)
	{
		GameModeMetas = GameModeMetasTable->FindRow<FRunGameModeMetas>(TEXT("0"), TEXT("Lookup Game Mode Metas"));
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

		if (NexusBlueprintClass)
		{
			if (ANexus* Nexus = GetWorld()->SpawnActor<ANexus>(NexusBlueprintClass, Grid->GetWorldNexusLocation(), FRotator::ZeroRotator))
			{
				Nexus->SetMaxHealth(GameModeMetas->PlayerInitialHealth);
			}
		}

		if (EnemySpawnerBlueprintClass)
		{
			EnemySpawner = GetWorld()->SpawnActor<AEnemySpawner>(EnemySpawnerBlueprintClass,
			                                                     Grid->GetWorldEnemySpawnerLocation(),
			                                                     FRotator::ZeroRotator);

			if (EnemySpawner)
			{
				EnemySpawner->SetNexusLocation(Grid->GetWorldNexusLocation());
			}
		}
	}
}

FTurretStats* ARunGameMode::GetTurretStats(FName TurretID)
{
	if (TurretDataTable)
	{
		return TurretDataTable->FindRow<FTurretStats>(TurretID, TEXT("Lookup Turret Stats"));
	}

	return nullptr;
}

FEnemyStats* ARunGameMode::GetEnemyStats(FName EnemyID)
{
	if (EnemyDataTable)
	{
		return EnemyDataTable->FindRow<FEnemyStats>(EnemyID, TEXT("Lookup Enemy Stats"));
	}

	return nullptr;
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
		if (bool bResult = Grid->RequestWallBuild(Location))
		{
			GameState->SpendPlayerCoins(GameModeMetas->WallPrice);
		}
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

void ARunGameMode::RequestTurretBuild(FName TurretID, const FVector& Location)
{
	if (TurretRegistry && TurretDataTable && GameState && GameState->IsBuildTurretMode() && Grid)
	{
		if (TSubclassOf<ATurretBase> TurretClass = TurretRegistry->GetTurretClass(TurretID))
		{
			if (const FTurretStats* TurretStats = GetTurretStats(TurretID))
			{
				if (GameState->GetPlayerCoins() < TurretStats->Price)
				{
					return;
				}

				if (bool bResult = Grid->RequestTurretBuild(&TurretClass, Location); bResult == true)
				{
					GameState->SpendPlayerCoins(TurretStats->Price);
				}
			}
		}
	}
}
