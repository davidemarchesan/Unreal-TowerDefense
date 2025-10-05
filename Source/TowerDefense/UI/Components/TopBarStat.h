// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"


struct FIconData
{
	FName Name;
	FName Color;
	float Width = 32.f;
};


struct FTextData
{
	FText Text;
	FName Color;
	float FontSize = 32.f;
};

/**
 * 
 */
class STopBarStat : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STopBarStat)
		{
		}

		SLATE_ARGUMENT(FIconData, Icon)
		SLATE_ARGUMENT(FTextData, Text)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetText(const FText& NewText);

private:
	FIconData Icon;
	FTextData Text;

	TSharedPtr<STextBlock> TextBlock;
};
