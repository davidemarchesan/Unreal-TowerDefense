// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LayoutEditorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ALayoutEditorGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	int32 MaxTurretWalls;

	int32 CurrentTurretWalls;

public:

	int32 RegisterTurretWallPlacement();
	
	int32 RegisterTurretWallRemoval();
	
	bool CanPlaceTurretWall() const { return CurrentTurretWalls < MaxTurretWalls; }

	int32 GetMaxTurretWalls() const { return MaxTurretWalls; }

	int32 GetCurrentTurretWalls() const { return CurrentTurretWalls; }
	
};
