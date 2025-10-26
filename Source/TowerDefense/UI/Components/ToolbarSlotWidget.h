// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SToolbarSlotWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SToolbarSlotWidget)
		{
			_IsSelected = false;
		}
		
		SLATE_ARGUMENT(FText, Name)
		SLATE_ARGUMENT(FText, Key)
		SLATE_ARGUMENT(FText, Price)
		
		SLATE_ARGUMENT(bool, IsSelected)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	FText Name;
	FText Key;
	FText Price;
	
	bool bSelected = false;
};
