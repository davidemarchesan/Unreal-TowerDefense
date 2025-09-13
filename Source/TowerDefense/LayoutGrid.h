// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enums/CellState.h"

#include "LayoutGrid.generated.h"

class AWall;
class ANavMeshBoundsVolume;
class UNavigationSystemV1;

UCLASS()
class TOWERDEFENSE_API ALayoutGrid : public AActor
{
	GENERATED_BODY()
	
public:	

	ALayoutGrid();

	virtual void Tick(float DeltaTime) override;

	void RequestPreview(FVector Location);

protected:

	virtual void BeginPlay() override;

private:

	// Path Finding
	ANavMeshBoundsVolume* NavMesh;

	UNavigationSystemV1* NavSystem;

	void InitializeNavMesh();

	void BuildNavMesh();

	// Grid
	TArray<TArray<ECellState>> Grid;

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 Rows = 20;

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 Cols = 30;

	void InitializeGrid();

	FVector Center;

	// Floor
	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* FloorComponent;

	void InitializeFloor();
	
	// Cells
	UPROPERTY(EditAnywhere, Category="BluePrints")
	float CellSize = 100.f;
	
	// Walls
	UPROPERTY(EditAnywhere, Category="BluePrints")
	TSubclassOf<AWall> WallBluePrintClass;

	UPROPERTY(EditAnywhere, Category="BluePrints")
	TSubclassOf<AWall> DefaultWallBluePrintClass;

	void InitializeWalls();

	void SpawnWall(int32 Col, int32 Row, ECellState State, const FString& Folder);

	// Preview wall
	AWall* PreviewWall = nullptr;

	int32 PreviewWallCol;
	int32 PreviewWallRow;

	void ResetPreviewWall();

};
