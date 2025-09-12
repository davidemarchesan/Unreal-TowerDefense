// Fill out your copyright notice in the Description page of Project Settings.


#include "LayoutGrid.h"
#include "Walls/Wall.h"

// Sets default values
ALayoutGrid::ALayoutGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALayoutGrid::BeginPlay()
{
	Super::BeginPlay();

	InitializeGrid();

	InitializePlane();
	InitializeWalls();
	
}

void ALayoutGrid::InitializeGrid()
{

	Center = FVector((Cols / 2) - 1, (Rows / 2) - 1, 0.f);

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

void ALayoutGrid::InitializePlane()
{
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

// Called every frame
void ALayoutGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

