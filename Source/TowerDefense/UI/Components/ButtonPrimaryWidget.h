// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"

class FText;

/**
 * 
 */
class SButtonPrimaryWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SButtonPrimaryWidget)
		{
		}

		SLATE_ARGUMENT(FText, ButtonText)
		SLATE_EVENT(FOnClicked, OnClicked)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	FText ButtonText;
	FOnClicked OnClicked;
};
