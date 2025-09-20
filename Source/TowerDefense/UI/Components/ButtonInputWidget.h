// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"

class FText;

/**
 * 
 */
class SButtonInputWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SButtonInputWidget)
		{
		}

		SLATE_ARGUMENT(FText, InputText)
		SLATE_ARGUMENT(FText, ButtonText)
		SLATE_EVENT(FOnClicked, OnClicked)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	FText InputText;
	FText ButtonText;
	FOnClicked OnClicked;
};
