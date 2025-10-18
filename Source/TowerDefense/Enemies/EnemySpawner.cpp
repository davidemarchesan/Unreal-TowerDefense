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

void AEnemySpawner::OnDefensePhaseStart(FWave Wave)
{
	HardCodedWave = Wave;
	StartWave();
}

void AEnemySpawner::StartWave()
{
	UE_LOG(LogTemp, Warning, TEXT("EnemySpawner: start wave"));

	CurrentEnemyGroup = 0;
	StartEnemiesGroup();
}

void AEnemySpawner::StartEnemiesGroup()
{
	GetWorldTimerManager().ClearTimer(EnemiesGroupSpawnTimerHandle);

	UE_LOG(LogTemp, Warning, TEXT("EnemySpawner: start enemies group index %d of %d"), CurrentEnemyGroup,
	       HardCodedWave.EnemiesGroups.Num());

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
		GameState->OnDefensePhaseStart.AddDynamic(this, &AEnemySpawner::OnDefensePhaseStart);
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
