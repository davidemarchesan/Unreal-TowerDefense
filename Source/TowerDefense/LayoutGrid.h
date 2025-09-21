// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enums/CellState.h"

#include "LayoutGrid.generated.h"

class AWall;
class ATurretWall;
class APreviewWall;
class ANavMeshBoundsVolume;
class UNavigationSystemV1;
class ANavigationData;
class AMainBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridInitialized);

UCLASS()
class TOWERDEFENSE_API ALayoutGrid : public AActor
{
	GENERATED_BODY()
	
public:	

	ALayoutGrid();

	virtual void Tick(float DeltaTime) override;

	void RequestPreviewWall(FVector Location);

	bool RequestWallBuild(FVector Location);

	void RequestWallRemoval(int32 Col, int32 Row);

	void RequestResetPreviewWall();

	bool IsGridInitialized() const { return bIsGridInitialized; }

	FVector GetWorldGridCenter() const { return WorldGridCenter; }

	FOnGridInitialized OnGridInitialized;

	void GetLayout(TArray<FIntPoint>& OutGridLayout);

protected:

	virtual void BeginPlay() override;

private:

	// Path Finding
	ANavMeshBoundsVolume* NavMesh;

	UNavigationSystemV1* NavSystem;

	ANavigationData* NavData;

	void InitializeNavMesh();

	void BuildNavMesh();

	bool IsPathValid();

	// Grid
	TArray<TArray<ECellState>> Grid;

	TMap<FIntPoint, AWall*> TurretWallsMap;

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 Rows = 20;

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 Cols = 30;

	void InitializeGrid();

	bool bIsGridInitialized = false;

	FVector WorldGridCenter;

	bool IsOutOfGrid(int32 Col, int32 Row);

	bool IsPositionValidToBuildOn(int32 Col, int32 Row);

	// Floor
	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* FloorComponent;

	void InitializeFloor();
	
	// Cells
	UPROPERTY(EditAnywhere, Category="BluePrints")
	float CellSize = 100.f;
	
	// Walls
	UPROPERTY(EditAnywhere, Category="BluePrints")
	TSubclassOf<AWall> TurretWallBluePrintClass;

	UPROPERTY(EditAnywhere, Category="BluePrints")
	TSubclassOf<AWall> DefaultWallBluePrintClass;

	void InitializeWalls();

	void LoadSavedLayout();

	void SpawnWall(int32 Col, int32 Row, ECellState State, const FString& Folder);

	// Preview wall
	bool bIsPreviewingWall = false;
	
	UPROPERTY(EditAnywhere, Category = "BluePrints")
	TSubclassOf<APreviewWall> PreviewWallBluePrintClass;

	APreviewWall* PreviewWall = nullptr;

	int32 PreviewWallCol;
	int32 PreviewWallRow;

	void ResetPreviewWall();

	// Ally Base
	void InitializeAllyBase();

	FVector WorldAllyBaseLocation;

	UPROPERTY(EditAnywhere, Category = "BluePrints")
	TSubclassOf<AMainBase> AllyBasePrintClass;

};
