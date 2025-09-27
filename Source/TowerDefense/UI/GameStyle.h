// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ISlateStyle;
class FSlateStyleSet;

/**
 * 
 */
class FGameStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:
	static TSharedPtr<FSlateStyleSet> StyleInstance;

	static void InitializeFonts();
	static void InitializeIcons();
	static void InitializeButtons();
};
