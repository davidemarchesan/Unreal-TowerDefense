// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "EnemyPawn.h"
#include "Data/Wave.h"
#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/GameStates/RunGameState.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::OnPhaseStart(ERunPhase NewPhase)
{
	switch (NewPhase)
	{
	case ERunPhase::Defense:
		StartWave();
		break;

	case ERunPhase::Setup:
		// GetWorldTimerManager().ClearTimer(EnemiesGroupSpawnTimerHandle);
		break;
	}
}

void AEnemySpawner::StartWave()
{
	TArray<FWaveEnemiesGroup> HardCodedEnemies = {
		FWaveEnemiesGroup(1.0, "Tank", 2),
		FWaveEnemiesGroup(1.0, "Fast", 5),
	};
	HardCodedWave = FWave(3.f, HardCodedEnemies);

	StartEnemiesGroup();
}

void AEnemySpawner::StartEnemiesGroup()
{
	GetWorldTimerManager().ClearTimer(EnemiesGroupSpawnTimerHandle);

	if (CurrentEnemyGroup >= HardCodedWave.EnemiesGroups.Num())
	{
		return;
	}

	FWaveEnemiesGroup Group = HardCodedWave.EnemiesGroups[CurrentEnemyGroup];

	GetWorldTimerManager().SetTimer(
		EnemyUnitSpawnTimerHandle,
		this,
		&AEnemySpawner::SpawnEnemy,
		Group.SpawnDelay,
		true
	);
}

void AEnemySpawner::GoToNextEnemiesGroup()
{
	CurrentEnemyGroup++;
	CurrentEnemyUnit = 0;

	if (CurrentEnemyGroup >= HardCodedWave.EnemiesGroups.Num())
	{
		// Wave is over
		GetWorldTimerManager().ClearTimer(EnemiesGroupSpawnTimerHandle);
		GetWorldTimerManager().ClearTimer(EnemyUnitSpawnTimerHandle);

		if (GameState)
		{
			GameState->GoToNextPhase();
		}
	}
	else
	{
		GetWorldTimerManager().SetTimer(
			EnemiesGroupSpawnTimerHandle,
			this,
			&AEnemySpawner::StartEnemiesGroup,
			HardCodedWave.SpawnDelay,
			false
		);
	}
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<ARunGameMode>();
	if (GameMode)
	{
		EnemyDataTable = GameMode->GetEnemyDataTable();
	}

	GameState = GetWorld()->GetGameState<ARunGameState>();
	if (GameState)
	{
		GameState->OnPhaseStart.AddDynamic(this, &AEnemySpawner::OnPhaseStart);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	if (CurrentEnemyGroup >= HardCodedWave.EnemiesGroups.Num())
	{
		return;
	}

	FWaveEnemiesGroup Group = HardCodedWave.EnemiesGroups[CurrentEnemyGroup];

	if (const TSubclassOf<AEnemyPawn> EnemyClass = GameMode->EnemyRegistry->GetEnemyClass(Group.EnemyId))
	{
		AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, GetActorLocation(), GetActorRotation());
		Enemy->SetDestination(NexusLocation);

		CurrentEnemyUnit++;

		if (CurrentEnemyUnit >= Group.Count)
		{
			// This group of enemies is over
			GetWorldTimerManager().ClearTimer(EnemyUnitSpawnTimerHandle);

			GoToNextEnemiesGroup();
		}
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
