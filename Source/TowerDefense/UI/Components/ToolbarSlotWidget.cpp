// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolbarSlotWidget.h"

#include "TowerDefense/UI/GameStyle.h"
#include "Widgets/Layout/SScaleBox.h"


void SToolbarSlotWidget::Construct(const FArguments& InArgs)
{
	// Const
	const float SlotWidth = 120.f;
	const float SlotHeight = SlotWidth;

	const float SlotBorderRadius = 24.f;
	const float SlotBorderWidth = 3.f;
	const float SlotInternalPadding = 10.f;

	const float PriceIconWidth = 20.f;
	const float PriceIconHeight = PriceIconWidth;

	// Input
	Name = InArgs._Name;
	Key = InArgs._Key;
	Price = InArgs._Price;
	
	bSelected = InArgs._IsSelected;

	// Build slate widget
	ChildSlot[
		
		SNew(SBorder)
		.BorderImage(
			new FSlateRoundedBoxBrush(
				FGameStyle::Get().GetColor("TowerDefense.Color.Gunmetal"),
				SlotBorderRadius,
				bSelected ? FLinearColor::White : FLinearColor::Transparent,
				SlotBorderWidth
			)
		)
		[

			SNew(SBox)
			.WidthOverride(SlotWidth)
			.HeightOverride(SlotHeight)
			.Padding(SlotInternalPadding)
			[

				SNew(SOverlay)

				// Slot name
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Justification(ETextJustify::Center)
					.Text(Name)
					.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.sm"))
					.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
				]

				// Slot number
				+ SOverlay::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				[
					SNew(STextBlock)
					.Justification(ETextJustify::Center)
					.Text(Key)
					.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.xs"))
					.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
				]

				// Slot price (not required)
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Bottom)
				[

					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.Padding(0.f, 0.f, 5.f, 0.f)
					.AutoWidth()
					[
						SNew(SBox)
						.WidthOverride(PriceIconWidth)
						.HeightOverride(PriceIconHeight)
						[

							SNew(SScaleBox)
							.Stretch(EStretch::ScaleToFit)
							.StretchDirection(EStretchDirection::DownOnly)
							[

								SNew(SImage)
								.Image(FGameStyle::Get().GetBrush("TowerDefense.Icons.Coins"))
								.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
							]

						]
					]

					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text(Price)
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.xs"))
						.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
					]

				]

			]

		]

	];
}
