// Fill out your copyright notice in the Description page of Project Settings.


#include "TopBarStat.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/Engine.h"
#include "TowerDefense/UI/GameStyle.h"
#include "Widgets/Layout/SScaleBox.h"

void STopBarStat::Construct(const FArguments& InArgs)
{
	Text = InArgs._Text;
	Icon = InArgs._Icon;

	const FMargin ContainerPadding = FMargin(2.f);
	const FMargin IconMargin = FMargin(0.f, 0.f, 6.f, 0.f);

	ChildSlot
	[

		SNew(SBox)
		.Padding(ContainerPadding)
		[

			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.AutoWidth()
			[

				SNew(SHorizontalBox)

				// Icon
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				.AutoWidth()
				[

					SNew(SBox)
					.WidthOverride(Icon.Width)
					.HeightOverride(Icon.Width)
					.Padding(IconMargin)
					[

						SNew(SScaleBox)
						.Stretch(EStretch::ScaleToFit)
						.StretchDirection(EStretchDirection::DownOnly)
						[

							SNew(SImage)
							.Image(FGameStyle::Get().GetBrush(Icon.Name))
							.ColorAndOpacity(FGameStyle::Get().GetColor(Icon.Color))
						]

					]

				]

				// Text
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(Text.Text)
					.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.md"))
					.ColorAndOpacity(FGameStyle::Get().GetColor(Text.Color))
				]
				
			]
			
		]

	];
}
