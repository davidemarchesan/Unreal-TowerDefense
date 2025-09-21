// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GridLayoutSave.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGridLayoutSave : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FIntPoint> Layout;
	
};
