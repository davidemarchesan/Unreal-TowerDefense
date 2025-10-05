// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SHealthBarWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHealthBarWidget)
		{
		}

		SLATE_ARGUMENT(float, HealthPercent)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetHealthPercent(float InPercent);

private:

	TSharedPtr<SBox> HealthBarBox;
	
	float HealthPercent;
};
