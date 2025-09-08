// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class STurretBuildMenu;
class ATopDownPlayerController;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	void RequestBuildTurret();

private:

	TSharedPtr<STurretBuildMenu> BuildMenu;
	TSharedPtr<class SWidget> BuildMenuContainer;

	ATopDownPlayerController* PC;
	
};
