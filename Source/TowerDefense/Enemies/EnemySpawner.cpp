// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "EnemyPawn.h"
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
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&AEnemySpawner::SpawnEnemy,
			2.0f,
			true
		);
		break;

	case ERunPhase::Setup:
		GetWorldTimerManager().ClearTimer(TimerHandle);
		break;
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

	ARunGameState* GameState = GetWorld()->GetGameState<ARunGameState>();
	if (GameState)
	{
		GameState->OnPhaseStart.AddDynamic(this, &AEnemySpawner::OnPhaseStart);
	}
}

void AEnemySpawner::SpawnEnemy()
{

	if (TSubclassOf<AEnemyPawn> EnemyClass = GameMode->EnemyRegistry->GetEnemyClass(TEXT("Tank")))
	{
		AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, GetActorLocation(), GetActorRotation());
		Enemy->SetDestination(NexusLocation);
	}
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
