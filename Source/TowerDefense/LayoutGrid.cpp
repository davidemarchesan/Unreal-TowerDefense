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

	// Init empty grid
	Grid.SetNum(Cols);
	for (int32 Col = 0; Col < Cols; Col++)
	{
		Grid[Col].SetNum(Rows);
		for (int32 Row = 0; Row < Rows; Row++)
		{

			if (Col == 0 || Col == (Cols - 1) || Row == 0 || Row == (Rows - 1)) {

				Grid[Col][Row] = ECellState::DefaultWall;

				FActorSpawnParameters SpawnParams;
				FString WallName = FString::Printf(TEXT("Wall_%d_%d"), Row, Col);
				SpawnParams.Name = FName(*WallName);

				AActor* SpawnedWall = GetWorld()->SpawnActor<AWall>(DefaultWallBluePrintClass, FVector((Row * CellSize), (Col * CellSize), 0.f), FRotator::ZeroRotator, SpawnParams);

				if (SpawnedWall)
				{
					SpawnedWall->SetFolderPath(TEXT("Walls/Outer"));
					SpawnedWall->SetActorLabel(*WallName);
				}
			}
			else {
				Grid[Col][Row] = ECellState::Empty;
			}
		}
	}
	
}

// Called every frame
void ALayoutGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

