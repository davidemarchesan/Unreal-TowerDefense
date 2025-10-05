// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "Widgets/Colors/SColorBlock.h"

void SHealthBarWidget::Construct(const FArguments& InArgs)
{
	HealthPercent = InArgs._HealthPercent;

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			
			SNew(SBox)
			.WidthOverride(100.f)
			.HeightOverride(20.f)
			[

				SNew(SBorder)
				.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
				.BorderBackgroundColor(FLinearColor::Black)
				.Padding(3.f)
				[

					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SAssignNew(HealthBarBox, SBox)
						.WidthOverride(94.f)
						.HeightOverride(20.f)
						[
						
							SNew(SBorder)
							.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
							.BorderBackgroundColor(FLinearColor::Red)
						]
					]
				
				]


			]

		]


	];
	// ChildSlot
	// [
	// 	SNew(SOverlay)
	//
	// 	+ SOverlay::Slot()
	// 	[
	// 		SNew(SColorBlock)
	// 		.Color(FLinearColor::Black)
	// 		.Size(FVector2D(1, 1))
	// 	]
	//
	// 	+ SOverlay::Slot()
	// 	[
	// 		SAssignNew(HealthBarBox, SBox)
	// 		.WidthOverride(1.f)
	// 		.HeightOverride(1.f)
	// 		[
	// 			SNew(SColorBlock)
	// 			.Color(FLinearColor::Yellow)
	// 		]
	// 	]
	// ];
}

void SHealthBarWidget::SetHealthPercent(float InPercent)
{
	if (HealthBarBox)
	{
		HealthPercent = FMath::Clamp(InPercent, 0.0f, 1.0f);
		HealthBarBox->SetWidthOverride(94.f * HealthPercent);
	}
}
