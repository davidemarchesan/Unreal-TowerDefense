// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LayoutEditorHUD.generated.h"

class ALayoutEditorPlayerController;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ALayoutEditorHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	void ToggleBuildMode(bool _bIsBuildMode);

private:
	ALayoutEditorPlayerController* PlayerController;

	bool bIsBuildMode = false;

	// Components
	TSharedPtr<SBorder> BuildModeBorder;

	TSharedPtr<SBox> StandardModeBox;
	TSharedPtr<SBox> BuildModeBox;

	// Button callbacks
	FReply OnToggleBuildMode();

	void UpdateComponentsOnBuildMode();
};
