// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TowerDefenseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTowerDefenseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void SaveGridLayout(TArray<FIntPoint> &Layout);

	UFUNCTION()
	TArray<FIntPoint> LoadGridLayout();
	
};
