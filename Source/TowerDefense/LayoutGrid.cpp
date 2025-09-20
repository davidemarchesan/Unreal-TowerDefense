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

// Sets default values
ALayoutGrid::ALayoutGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));
	FloorComponent->SetupAttachment(RootComponent);

	UE_LOG(LogTemp, Warning, TEXT("ALayoutGrid::ALayoutGrid()"));

}

// Called when the game starts or when spawned
void ALayoutGrid::BeginPlay()
{
	Super::BeginPlay();

	InitializeGrid();

	InitializeFloor();
	InitializeWalls();
	InitializeAllyBase();

	InitializeNavMesh();
	BuildNavMesh();

}

void ALayoutGrid::RequestPreview(FVector Location)
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

	ECellState State = Grid[Col][Row];

	if (State == ECellState::Empty)
	{

		// It is ok to preview
		PreviewWallCol = Col;
		PreviewWallRow = Row;

		if (PreviewWall == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning preview wall"));
			PreviewWall = GetWorld()->SpawnActor<APreviewWall>(PreviewWallBluePrintClass, FVector((Row * CellSize), (Col * CellSize), 0.f), FRotator::ZeroRotator);

			if (PreviewWall)
			{
				FString WallName = FString::Printf(TEXT("PreviewWall"), Col, Row);
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

void ALayoutGrid::RequestWallBuild()
{

	if (IsPositionValidToBuildOn(PreviewWallCol, PreviewWallRow))
	{
		SpawnWall(PreviewWallCol, PreviewWallRow, ECellState::TurretWall, TEXT("TurretWalls"));
		ResetPreviewWall();
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
			else {

				const TArray<FNavPathPoint>& Points = Result.Path->GetPathPoints();

				for (int32 i = 0; i < Points.Num(); i++)
				{
					const FVector& P = Points[i].Location;

					// Disegna sfera per ogni waypoint
					DrawDebugSphere(GetWorld(), P, 20.f, 12, FColor::Green, false, 5.f);

					// Disegna linea verso il prossimo
					if (i + 1 < Points.Num())
					{
						const FVector& Next = Points[i + 1].Location;
						DrawDebugLine(GetWorld(), P, Next, FColor::Yellow, false, 5.f, 0, 2.f);
					}
				}

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

	//// 1.A Check if at least a wall is on side
	//bool bHaveAdjacentWall = false;
	//TArray<FIntPoint> AdjacentSides = {
	//	FIntPoint(1, 0),	// Right
	//	FIntPoint(-1, 0),	// Left
	//	FIntPoint(0, 1),	// Top
	//	FIntPoint(0, -1),	// Bottom
	//};

	//for (const FIntPoint& AdjacentSide : AdjacentSides)
	//{
	//	int32 ColToCheck = Col + AdjacentSide.X;
	//	int32 RowToCheck = Row + AdjacentSide.Y;

	//	if (IsOutOfGrid(ColToCheck, RowToCheck)) continue;

	//	if (
	//		Grid[ColToCheck][RowToCheck] == ECellState::DefaultWall 
	//		|| Grid[ColToCheck][RowToCheck] == ECellState::TurretWall
	//	)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Has at least on adjacent wall"));
	//		bHaveAdjacentWall = true;
	//		break;
	//	}
	//}

	//// 1.B If there are no walls on adjacent sides
	//// check if there are on adjance diagonals
	//// Can not build on diagonals (but can build in the middle of nowhere)
	//if (bHaveAdjacentWall == false)
	//{
	//	bool bHaveAdjacentDiagonalWall = false;
	//	TArray<FIntPoint> DiagonalAdjacentSides = {
	//		FIntPoint(1, 1),	// Top-Right
	//		FIntPoint(-1, 1),	// Top-Left
	//		FIntPoint(1, -1),	// Bottom-Right
	//		FIntPoint(-1, -1),	// Bottom-Left
	//	};

	//	for (const FIntPoint& DiagonalAdjacentSide : DiagonalAdjacentSides)
	//	{
	//		int32 ColToCheck = Col + DiagonalAdjacentSide.X;
	//		int32 RowToCheck = Row + DiagonalAdjacentSide.Y;

	//		if (IsOutOfGrid(ColToCheck, RowToCheck)) continue;

	//		if (
	//			Grid[ColToCheck][RowToCheck] == ECellState::DefaultWall
	//			|| Grid[ColToCheck][RowToCheck] == ECellState::TurretWall
	//			)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("Yes, it has a diagonal wall! no build man"));
	//			bHaveAdjacentDiagonalWall = true;
	//			break;
	//		}

	//	}

	//	if (bHaveAdjacentDiagonalWall)
	//	{
	//		return false;
	//	}
	//}

	//// 2. Check side area
	//UE_LOG(LogTemp, Warning, TEXT("-------------------------"));
	//bool bIsPositionValid = false;

	//TArray<TArray<FIntPoint>> Sides = {
	//	{ FIntPoint(0, 2), FIntPoint(-2, 2), },		// Right
	//	{ FIntPoint(-2, 0), FIntPoint(-2, 2), },	// Left
	//	{ FIntPoint(-2, 2), FIntPoint(0, 2), },		// Top
	//	{ FIntPoint(-2, 2), FIntPoint(-2, 0), },	// Bottom
	//};

	//for (const TArray<FIntPoint>& Side : Sides)
	//{
	//	
	//	// Need just one valid side
	//	bool bIsSideValid = true;

	//	int32 XStartingPoint = Side[0].X;
	//	int32 XEndingPoint = Side[0].Y;

	//	int32 YStartingPoint = Side[1].X;
	//	int32 YEndingPoint = Side[1].Y;

	//	UE_LOG(LogTemp, Warning, TEXT("SIDE x: %d %d | y: %d %d ---------------------"), XStartingPoint, XEndingPoint, YStartingPoint, YEndingPoint);

	//	for (int32 X = XStartingPoint; X <= XEndingPoint; X++)
	//	{
	//		for (int32 Y = YStartingPoint; Y <= YEndingPoint; Y++)
	//		{
	//			int32 ColToCheck = Col + X;
	//			int32 RowToCheck = Row + Y;

	//			UE_LOG(LogTemp, Warning, TEXT("Checking %d %d"), X, Y);

	//			if (
	//				IsOutOfGrid(ColToCheck, RowToCheck)
	//				|| Grid[ColToCheck][RowToCheck] != ECellState::Empty)
	//			{
	//				UE_LOG(LogTemp, Warning, TEXT("XXXXX Failed at %d %d"), X, Y);
	//				bIsSideValid = false;
	//				break;
	//			}
	//		}

	//		if (bIsSideValid == false)
	//		{
	//			break;
	//		}
	//	}

	//	if (bIsSideValid == true)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("vvvvv Side is valid"));
	//		bIsPositionValid = true;
	//		break;
	//	}

	//}

	//return bIsPositionValid;

	// END - V2

	//// At least 3 sides has to be valid
	//// Check if there are at least 2 adjacent empty cells (both side and diagonal)
	//int32 NumberOfValidSides = 0;

	//TArray<TArray<FIntPoint>> Sides = {
	//	// Right
	//	{ 
	//		FIntPoint(1, 0), FIntPoint(2, 0),
	//		FIntPoint(1, 1), FIntPoint(2, 2),
	//		FIntPoint(1, -1), FIntPoint(2, -2),
	//	},

	//	// Left
	//	{ 
	//		FIntPoint(-1, 0), FIntPoint(-2, 0),
	//		FIntPoint(-1, -1), FIntPoint(-2, -2),
	//		FIntPoint(-1, 1), FIntPoint(-2, 2),
	//	},

	//	// Top
	//	{ 
	//		FIntPoint(0, 1), FIntPoint(0, 2), 
	//		FIntPoint(1, 1), FIntPoint(2, 2), 
	//		FIntPoint(-1, 1), FIntPoint(-2, 2), 
	//	},

	//	// Bottom
	//	{ 
	//		FIntPoint(0, -1), FIntPoint(0, -2),
	//		FIntPoint(1, -1), FIntPoint(2, -2),
	//		FIntPoint(-1, -1), FIntPoint(-2, -2),
	//	},
	//};

	//for (const TArray<FIntPoint>& Side : Sides)
	//{
	//	bool bIsSideValid = true;

	//	for (const FIntPoint& Cell : Side)
	//	{

	//		int32 ColToCheck = Col + Cell.X;
	//		int32 RowToCheck = Row + Cell.Y;

	//		if (
	//			IsOutOfGrid(ColToCheck, RowToCheck)
	//			|| Grid[ColToCheck][RowToCheck] != ECellState::Empty)
	//		{
	//			bIsSideValid = false;
	//			break;
	//		}
	//	}

	//	if (bIsSideValid)
	//	{
	//		NumberOfValidSides++;
	//	}
	//}

	//return NumberOfValidSides >= 3;
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
			if (Col == 0 || Col == (Cols - 1) || Row == 0 || Row == (Rows - 1)) {
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

	AActor* SpawnedWall = GetWorld()->SpawnActor<AWall>(BluePrintClass, FVector((Row * CellSize), (Col * CellSize), 0.f), FRotator::ZeroRotator);

	if (SpawnedWall)
	{
		FString WallName = FString::Printf(TEXT("Wall_%d_%d"), Col, Row);
		FString Path = FString::Printf(TEXT("Walls/%s"), *Folder);
		SpawnedWall->SetFolderPath(*Path);
		SpawnedWall->SetActorLabel(*WallName);
	}
}

void ALayoutGrid::ResetPreviewWall()
{
	if (PreviewWall)
	{
		PreviewWall->Destroy();
		PreviewWall = nullptr;

		PreviewWallCol = -1;
		PreviewWallRow = -1;
	}
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

