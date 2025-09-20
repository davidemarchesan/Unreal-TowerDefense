// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonInputWidget.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Brushes/SlateRoundedBoxBrush.h"

void SButtonInputWidget::Construct(const FArguments& InArgs)
{
	InputText = InArgs._InputText;
	ButtonText = InArgs._ButtonText;
	OnClicked = InArgs._OnClicked;

	FTextBlockStyle TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
	TextStyle.SetFontSize(20.f);

	const FMargin TextPadding = FMargin(8.f, 0.f);

	ChildSlot
	[
		SNew(SButton)
		.OnClicked(OnClicked)
		.ContentPadding(FMargin(0.f, 8.f))
		.Content()
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBorder)
				.BorderBackgroundColor(FLinearColor::Transparent)
				.Padding(TextPadding)
				[
					SNew(STextBlock)
					.Text(InArgs._InputText)
					.TextStyle(&TextStyle)
				]
			]

			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBorder)
				.BorderBackgroundColor(FLinearColor::Transparent)
				.Padding(TextPadding)
				[
					SNew(STextBlock)
					.Text(InArgs._ButtonText)
					.TextStyle(&TextStyle)
					.ColorAndOpacity(FLinearColor::White)
				]
			]
		]
	];
}
