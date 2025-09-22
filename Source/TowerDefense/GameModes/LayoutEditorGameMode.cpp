// Fill out your copyright notice in the Description page of Project Settings.


#include "LayoutEditorGameMode.h"

int32 ALayoutEditorGameMode::RegisterTurretWallPlacement()
{
	CurrentTurretWalls = FMath::Clamp((CurrentTurretWalls + 1), 0, MaxTurretWalls);
	UE_LOG(LogTemp, Warning, TEXT("CurrentTurretWalls placement: %d"), CurrentTurretWalls);
	return CurrentTurretWalls;
}

int32 ALayoutEditorGameMode::RegisterTurretWallRemoval()
{
	CurrentTurretWalls = FMath::Clamp((CurrentTurretWalls - 1), 0, MaxTurretWalls);
	UE_LOG(LogTemp, Warning, TEXT("CurrentTurretWalls removal: %d"), CurrentTurretWalls);
	return CurrentTurretWalls;
}
