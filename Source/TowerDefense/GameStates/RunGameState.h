// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TowerDefense/Enums/RunPhase.h"
#include "RunGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ARunGameState : public AGameStateBase
{
	GENERATED_BODY()

private:

	ERunPhase Phase;

	float PlayerHealth;
	
};
