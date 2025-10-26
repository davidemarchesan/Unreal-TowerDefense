// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense/PlayerControllers/ToolbarSlot.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SToolbarWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SToolbarWidget)
		{
		}

		SLATE_ARGUMENT(TArray<FToolbarSlot>, Slots)

		SLATE_ARGUMENT(FText, Name)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	TArray<FToolbarSlot> Slots;
};
