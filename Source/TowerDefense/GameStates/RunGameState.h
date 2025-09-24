// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TowerDefense/Enums/RunPhase.h"
#include "RunGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhaseStart);

class ARunGameMode;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ARunGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	// virtual void BeginPlay() override
	// {
	// 	Super::BeginPlay();
	// 	UE_LOG(LogTemp, Warning, TEXT(">>> RunGameState BeginPlay INLINE <<<"));
	// }
	virtual void BeginPlay() override;
	
private:

	ARunGameMode* GameMode;

	ERunPhase Phase = ERunPhase::BuyAndBuild;

	UFUNCTION()
	void OnGameReady();

	float PlayerHealth;

public:

	FOnPhaseStart OnPhaseStart;
};
