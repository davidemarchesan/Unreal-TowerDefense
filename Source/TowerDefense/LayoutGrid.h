// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enums/CellState.h"

#include "LayoutGrid.generated.h"

class AWall;

UCLASS()
class TOWERDEFENSE_API ALayoutGrid : public AActor
{
	GENERATED_BODY()
	
public:	

	ALayoutGrid();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	// Grid
	TArray<TArray<ECellState>> Grid;

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 Rows = 20;

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 Cols = 30;

	// Cells
	UPROPERTY(EditAnywhere, Category="BluePrints")
	float CellSize = 100.f;
	

	// Walls
	UPROPERTY(EditAnywhere, Category="BluePrints")
	TSubclassOf<AWall> WallBluePrintClass;

	UPROPERTY(EditAnywhere, Category="BluePrints")
	TSubclassOf<AWall> DefaultWallBluePrintClass;

};
