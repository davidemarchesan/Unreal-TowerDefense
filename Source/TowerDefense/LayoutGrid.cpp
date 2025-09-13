// Fill out your copyright notice in the Description page of Project Settings.


#include "LayoutGrid.h"
#include "Walls/Wall.h"
#include "NavigationSystem.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Components/BrushComponent.h"
#include "EngineUtils.h"

//creare gamemode
//done - creare controller e input diversi
//spawnare wall
//mettere le basi
//calcolare la navmesh
//spawnare muri
//salvare layout
//caricare layout

// Sets default values
ALayoutGrid::ALayoutGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));
	FloorComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALayoutGrid::BeginPlay()
{
	Super::BeginPlay();

	InitializeGrid();

	InitializeFloor();
	InitializeWalls();

	InitializeNavMesh();
	BuildNavMesh();
	
}

void ALayoutGrid::RequestPreview(FVector Location)
{

	UE_LOG(LogTemp, Warning, TEXT("Grid: they asked me if %s is available"), *Location.ToString());

	int32 Col = FMath::RoundToInt(Location.Y / 100.f);
	int32 Row = FMath::RoundToInt(Location.X / 100.f);

	if (Col == PreviewWallCol && Row == PreviewWallRow)
	{
		// Same spot, no need to set again the same position
		UE_LOG(LogTemp, Warning, TEXT("Same spot, no need to set again the same position"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Grid: converted are %d %d"), Col, Row);

	if (Col < 0 || Row < 0 || Col >= Cols || Row >= Rows)
	{
		UE_LOG(LogTemp, Warning, TEXT("out of bounds"));
		ResetPreviewWall();
	}

	ECellState State = Grid[Col][Row];
	UE_LOG(LogTemp, Warning, TEXT("Grid: state is %d"), (uint8)State);

	if (State == ECellState::Empty)
	{

		// It is ok to preview
		UE_LOG(LogTemp, Warning, TEXT("it is ok to preview"));
		PreviewWallCol = Col;
		PreviewWallRow = Row;

		if (PreviewWall == nullptr)
		{
			PreviewWall = GetWorld()->SpawnActor<AWall>(WallBluePrintClass, FVector((Row * CellSize), (Col * CellSize), 0.f), FRotator::ZeroRotator);
		}
		else
		{
			PreviewWall->SetActorLocation(FVector((Row * CellSize), (Col * CellSize), 0.f));
		}

	}
	else
	{
		ResetPreviewWall();
	}

}

void ALayoutGrid::InitializeNavMesh()
{
	for (TActorIterator<ANavMeshBoundsVolume> It(GetWorld()); It; ++It)
	{
		NavMesh = *It;

		if (NavMesh)
		{
			NavMesh->SetActorLocation(Center);
			break;
		}
	}

	// Get nav system
	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
}

void ALayoutGrid::BuildNavMesh()
{

	if (NavSystem)
	{
		NavSystem->Build();
	}

}

void ALayoutGrid::InitializeGrid()
{

	Center = FVector(((Cols - 1) / 2.0f) * CellSize, ((Rows - 1) / 2.0f) * CellSize, 0.f);

	Grid.SetNum(Cols);
	for (int32 Col = 0; Col < Cols; Col++)
	{
		Grid[Col].SetNum(Rows);
		for (int32 Row = 0; Row < Rows; Row++)
		{
			Grid[Col][Row] = ECellState::Empty;
		}
	}
}

void ALayoutGrid::InitializeFloor()
{
	// Putting the floor at the grid center, and scaling it
	FVector CurrentLocation = FloorComponent->GetRelativeLocation();
	FVector CurrentScale = FloorComponent->GetRelativeScale3D();

	FloorComponent->SetRelativeLocation(FVector(Center.X, Center.Y, CurrentLocation.Z));
	FloorComponent->SetWorldScale3D(FVector(Cols, Rows, CurrentScale.Z));

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
	Grid[Col][Row] = State;

	AActor* SpawnedWall = GetWorld()->SpawnActor<AWall>(DefaultWallBluePrintClass, FVector((Row * CellSize), (Col * CellSize), 0.f), FRotator::ZeroRotator);

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

// Called every frame
void ALayoutGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

