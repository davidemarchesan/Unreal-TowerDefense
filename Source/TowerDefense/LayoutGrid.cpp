// Fill out your copyright notice in the Description page of Project Settings.


#include "LayoutGrid.h"
#include "Walls/Wall.h"
#include "Walls/PreviewWall.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "NavigationData.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Components/BrushComponent.h"
#include "EngineUtils.h"
#include "TowerDefense/Enums/PreviewWallState.h"
#include "MainBase.h"
#include "DrawDebugHelpers.h"
#include "TowerDefenseGameInstance.h"

// Sets default values
ALayoutGrid::ALayoutGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));
	FloorComponent->SetupAttachment(RootComponent);
}

void ALayoutGrid::GetLayout(TArray<FIntPoint>& OutGridLayout)
{
	OutGridLayout.Empty();

	for (int32 Col = 0; Col < Cols; Col++)
	{
		for (int32 Row = 0; Row < Rows; Row++)
		{
			if (Grid[Col][Row] == ECellState::TurretWall)
			{
				OutGridLayout.Add(FIntPoint(Col, Row));
			}
		}
	}
}

// Called when the game starts or when spawned
void ALayoutGrid::BeginPlay()
{
	Super::BeginPlay();

	InitializeGrid();

	InitializeFloor();
	InitializeWalls();
	LoadSavedLayout();
	InitializeAllyBase();

	InitializeNavMesh();
	BuildNavMesh();
}

void ALayoutGrid::RequestPreviewWall(FVector Location)
{
	if (bIsGridInitialized == false)
	{
		return;
	}

	int32 Col = FMath::RoundToInt(Location.Y / 100.f);
	int32 Row = FMath::RoundToInt(Location.X / 100.f);

	if (Col == PreviewWallCol && Row == PreviewWallRow)
	{
		// Same spot, no need to set again the same position
		return;
	}

	if (IsOutOfGrid(Col, Row))
	{
		ResetPreviewWall();
		return;
	}

	PreviewWallCol = Col;
	PreviewWallRow = Row;

	ECellState State = Grid[Col][Row];

	if (State == ECellState::Empty)
	{
		// It is ok to preview
		bIsPreviewingWall = true;

		if (PreviewWall == nullptr)
		{
			PreviewWall = GetWorld()->SpawnActor<APreviewWall>(PreviewWallBluePrintClass,
			                                                   FVector((Row * CellSize), (Col * CellSize), 0.f),
			                                                   FRotator::ZeroRotator);

			if (PreviewWall)
			{
				FString WallName = FString::Printf(TEXT("PreviewWall"));
				FString Path = FString::Printf(TEXT("Walls"));
				PreviewWall->SetFolderPath(*Path);
				PreviewWall->SetActorLabel(*WallName);
			}
		}
		else
		{
			PreviewWall->SetActorLocation(FVector((Row * CellSize), (Col * CellSize), 0.f));
		}

		bool bIsPositionValid = IsPositionValidToBuildOn(Col, Row);
		PreviewWall->SetPreviewState(bIsPositionValid ? EPreviewWallState::Valid : EPreviewWallState::Invalid);
	}
	else
	{
		ResetPreviewWall();
	}
}

bool ALayoutGrid::RequestWallBuild(FVector Location)
{
	if (Grid[PreviewWallCol][PreviewWallRow] == ECellState::Empty && IsPositionValidToBuildOn(
		PreviewWallCol, PreviewWallRow))
	{
		SpawnWall(PreviewWallCol, PreviewWallRow, ECellState::TurretWall, TEXT("TurretWalls"));
		ResetPreviewWall();

		return true;
	}

	return false;
}

void ALayoutGrid::RequestWallRemoval(int32 Col, int32 Row)
{
	if (Grid[Col][Row] == ECellState::TurretWall)
	{
		// Remove wall
		Grid[Col][Row] = ECellState::Empty;

		FIntPoint Coord(Col, Row);

		AWall** Wall = TurretWallsMap.Find(Coord);

		if (Wall)
		{
			TurretWallsMap[Coord]->Destroy();
			TurretWallsMap.Remove(Coord);
		}
	}
}

void ALayoutGrid::RequestResetPreviewWall()
{
	ResetPreviewWall();
}

void ALayoutGrid::InitializeNavMesh()
{
	for (TActorIterator<ANavMeshBoundsVolume> It(GetWorld()); It; ++It)
	{
		NavMesh = *It;

		if (NavMesh)
		{
			NavMesh->SetActorLocation(WorldGridCenter);


			break;
		}
	}

	// Get nav system
	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSystem)
	{
		NavData = NavSystem->GetNavDataForAgentName(FName("Davide"));
	}
}

void ALayoutGrid::BuildNavMesh()
{
	if (NavSystem)
	{
		NavSystem->Build();
	}
}

bool ALayoutGrid::IsPathValid()
{
	if (NavSystem)
	{
		// Yes, we need to run this every time
		NavSystem->Build();

		FVector StartPosition((1.5f * CellSize), (1.5f * CellSize), 0.f);

		FPathFindingQuery Query(
			nullptr,
			*NavData,
			StartPosition,
			WorldAllyBaseLocation
		);

		FNavPathSharedPtr NavPath;
		FPathFindingResult Result = NavSystem->FindPathSync(Query);

		if (Result.IsSuccessful() && Result.Path.IsValid())
		{
			if (Result.Path->IsPartial())
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}

void ALayoutGrid::InitializeGrid()
{
	WorldGridCenter = FVector(((Rows - 1) / 2.0f) * CellSize, ((Cols - 1) / 2.0f) * CellSize, 0.f);

	Grid.SetNum(Cols);
	for (int32 Col = 0; Col < Cols; Col++)
	{
		Grid[Col].SetNum(Rows);
		for (int32 Row = 0; Row < Rows; Row++)
		{
			Grid[Col][Row] = ECellState::Empty;
		}
	}

	bIsGridInitialized = true;

	OnGridInitialized.Broadcast();
}

bool ALayoutGrid::IsOutOfGrid(int32 Col, int32 Row)
{
	return Col < 0 || Row < 0 || Col >= Cols || Row >= Rows;
}

bool ALayoutGrid::IsPositionValidToBuildOn(const int32 Col, const int32 Row)
{
	if (bIsGridInitialized == false) return false;

	if (IsOutOfGrid(Col, Row)) return false;

	if (IsPathValid() == false) return false;

	return true;
}

void ALayoutGrid::InitializeFloor()
{
	// Putting the floor at the grid center, and scaling it
	FVector CurrentLocation = FloorComponent->GetRelativeLocation();
	FVector CurrentScale = FloorComponent->GetRelativeScale3D();

	FloorComponent->SetRelativeLocation(FVector(WorldGridCenter.X, WorldGridCenter.Y, CurrentLocation.Z));
	FloorComponent->SetWorldScale3D(FVector(Rows, Cols, CurrentScale.Z));
}

void ALayoutGrid::InitializeWalls()
{
	for (int32 Col = 0; Col < Cols; Col++)
	{
		for (int32 Row = 0; Row < Rows; Row++)
		{
			if (Col == 0 || Col == (Cols - 1) || Row == 0 || Row == (Rows - 1))
			{
				SpawnWall(Col, Row, ECellState::DefaultWall, TEXT("Outer"));
			}
		}
	}

	// Enemy Base walls
	for (int32 i = 1; i <= 5; i++)
	{
		SpawnWall(3, i, ECellState::DefaultWall, TEXT("EnemyBase"));
	}

	// Ally Base walls
	for (int32 j = (Rows - 2); j >= (Rows - 6); j--)
	{
		SpawnWall((Cols - 4), j, ECellState::DefaultWall, TEXT("AllyBase"));
	}
}

void ALayoutGrid::LoadSavedLayout()
{
	// Temp
	UTowerDefenseGameInstance* GameInstance = Cast<UTowerDefenseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		TArray<FIntPoint> SavedGridLayout = GameInstance->LoadGridLayout();

		if (SavedGridLayout.Num() > 0)
		{
			for (int32 I = 0; I < SavedGridLayout.Num(); I++)
			{
				UE_LOG(LogTemp, Warning, TEXT("Loaded grid %d %d"), SavedGridLayout[I].X, SavedGridLayout[I].Y);

				SpawnWall(SavedGridLayout[I].X, SavedGridLayout[I].Y, ECellState::TurretWall, TEXT("TurretWalls"));
				
			}
		}
	}

	// End Temp
}

void ALayoutGrid::SpawnWall(int32 Col, int32 Row, ECellState State, const FString& Folder)
{
	if (IsOutOfGrid(Col, Row)) return;

	Grid[Col][Row] = State;

	TSubclassOf<AWall> BluePrintClass;
	switch (State)
	{
	case ECellState::DefaultWall:
		BluePrintClass = DefaultWallBluePrintClass;
		break;
	case ECellState::TurretWall:
	default:
		BluePrintClass = TurretWallBluePrintClass;
		break;
	}

	AWall* SpawnedWall = GetWorld()->SpawnActor<AWall>(BluePrintClass, FVector((Row * CellSize), (Col * CellSize), 0.f),
	                                                   FRotator::ZeroRotator);

	if (SpawnedWall)
	{
		FString WallName = FString::Printf(TEXT("Wall_%d_%d"), Col, Row);
		FString Path = FString::Printf(TEXT("Walls/%s"), *Folder);
		SpawnedWall->SetFolderPath(*Path);
		SpawnedWall->SetActorLabel(*WallName);
		SpawnedWall->SetCoord(Col, Row);

		TurretWallsMap.Add(FIntPoint(Col, Row), SpawnedWall);
	}
}

void ALayoutGrid::ResetPreviewWall()
{
	if (bIsPreviewingWall == false)
	{
		return;
	}

	if (PreviewWall)
	{
		PreviewWall->Destroy();
		PreviewWall = nullptr;

		PreviewWallCol = -1;
		PreviewWallRow = -1;
	}

	bIsPreviewingWall = false;
}

void ALayoutGrid::InitializeAllyBase()
{
	float Col = Cols - 2.5f;
	float Row = Rows - 2.5f;

	WorldAllyBaseLocation = FVector((Row * CellSize), (Col * CellSize), 0.f);

	GetWorld()->SpawnActor<AMainBase>(AllyBasePrintClass, WorldAllyBaseLocation, FRotator::ZeroRotator);

	if (bIsGridInitialized)
	{
		// Enemy spawn
		Grid[1][1] = ECellState::Disabled;
		Grid[1][2] = ECellState::Disabled;
		Grid[2][1] = ECellState::Disabled;
		Grid[2][2] = ECellState::Disabled;

		// Ally base
		Grid[Cols - 2][Rows - 2] = ECellState::Disabled;
		Grid[Cols - 2][Rows - 3] = ECellState::Disabled;
		Grid[Cols - 3][Rows - 2] = ECellState::Disabled;
		Grid[Cols - 3][Rows - 3] = ECellState::Disabled;
	}
}

// Called every frame
void ALayoutGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
