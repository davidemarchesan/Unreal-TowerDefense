// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonPrimaryWidget.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/Engine.h"

void SButtonPrimaryWidget::Construct(const FArguments& InArgs)
{
	ButtonText = InArgs._ButtonText;
	OnClicked = InArgs._OnClicked;

	FTextBlockStyle TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
	TextStyle.SetFontSize(20.f);

	ChildSlot
	[

		SNew(SButton)
		.OnClicked(OnClicked)
		.ContentPadding(FMargin(8.0f, 8.0f))
		[
			SNew(STextBlock)
			.Text(ButtonText)
			.Justification(ETextJustify::Center)
			.TextStyle(&TextStyle)
		]

	];
}
