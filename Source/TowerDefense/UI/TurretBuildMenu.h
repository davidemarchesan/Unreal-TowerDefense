// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"

class AGameHUD;

/**
 * 
 */
class STurretBuildMenu : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(STurretBuildMenu) {}
		SLATE_ARGUMENT(class AGameHUD*, OwnerHUD)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	AGameHUD* OwnerHUD;

	FReply OnBuildTurret();

};
