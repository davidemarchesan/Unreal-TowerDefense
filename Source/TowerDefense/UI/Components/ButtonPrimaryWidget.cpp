// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonPrimaryWidget.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/Engine.h"
#include "TowerDefense/UI/GameStyle.h"

void SButtonPrimaryWidget::Construct(const FArguments& InArgs)
{
	ButtonText = InArgs._ButtonText;
	OnClicked = InArgs._OnClicked;

	FSlateFontInfo Font = FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold");
	Font.Size = 40;
		
	ChildSlot
	[

		SNew(SButton)
		.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("TowerDefense.Button"))
		.OnClicked(OnClicked)
		[
			SNew(STextBlock)
			.Text(ButtonText)
			.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Gunmetal"))
			// .ColorAndOpacity(FLinearColor::White)
			.Font(Font)
		]

	];
}
