// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"

#include "TowerDefense/LayoutGrid.h"

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeGrid();
}

void ARunGameMode::InitializeGrid()
{
	if (!GridBlueprintClass)
	{
		return;
	}
	if (ALayoutGrid* Grid = GetWorld()->SpawnActor<ALayoutGrid>(GridBlueprintClass, FVector::ZeroVector, FRotator::ZeroRotator))
	{
		Grid->Initialize(GridCols, GridRows);
	}
	
}
