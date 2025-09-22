// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATestHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;
	
};
