// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHUD.h"

#include "GameStyle.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

void ATestHUD::BeginPlay()
{
	Super::BeginPlay();

	FSlateFontInfo MainMenuItemFont = FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold");
	MainMenuItemFont.Size = 80;

	FSlateFontInfo TitleFont = FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold");
	TitleFont.Size = 120;

	if (GEngine && GEngine->GameViewport)
	{
		const TSharedRef<SOverlay> RootOverlay = SNew(SOverlay);

		// Test below
		RootOverlay->AddSlot()
		           .HAlign(HAlign_Fill)
		           .VAlign(VAlign_Fill)
		[

			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
			.BorderBackgroundColor(FGameStyle::Get().GetColor("TowerDefense.Color.Gunmetal"))
			[

				SNew(SVerticalBox)

				// Title
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.AutoHeight()
				[
					SNew(SBox)
					.Padding(FMargin(0, 20))
					[

						SNew(STextBlock)
						.Text(FText::FromString("Tower Defense"))
						.Font(TitleFont)
						.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Cerise"))

					]
				]

				// Main Menu Items
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[

					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.AutoHeight()
					[

						SNew(SBox)
						.Padding(FMargin(0, 10))
						[

							SNew(STextBlock)
							.Text(FText::FromString("Play"))
							.Font(MainMenuItemFont)
							.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.TeaGreen"))

						]

					]

					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.AutoHeight()
					[

						SNew(SBox)
						.Padding(FMargin(0, 10))
						[

							SNew(STextBlock)
							.Text(FText::FromString("Edit Layout"))
							.Font(MainMenuItemFont)
							.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.TeaGreen"))

						]

					]

					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.AutoHeight()
					[

						SNew(SBox)
						.Padding(FMargin(0, 10))
						[

							SNew(STextBlock)
							.Text(FText::FromString("Exit"))
							.Font(MainMenuItemFont)
							.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Bittersweet"))

						]

					]
				]


				// + SVerticalBox::Slot()
				// .HAlign(HAlign_Center)
				// [
				//
				// 	SNew(SBox)
				// 	[
				//
				// 		SNew(SButton)
				// 		.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("TowerDefense.Button"))
				// 		[
				// 			SNew(STextBlock)
				// 			.Text(FText::FromString("TestHUD"))
				// 		]
				// 	]
				//
				// ]

			]


		];

		// Do not edit this overlay
		RootOverlay->AddSlot()
		           .HAlign(HAlign_Left)
		           .VAlign(VAlign_Top)
		[

			SNew(SButton)
			.OnClicked_Lambda([]() -> FReply
			{
				FGameStyle::Shutdown();
				FGameStyle::Initialize();
				return FReply::Handled();
			})
			.Text(FText::FromString("Reload FGameStyles"))

		];

		UE_LOG(LogTemp, Warning, TEXT("TestHUD::BeginPlay() AddViewportWidgetContent"));

		GEngine->GameViewport->AddViewportWidgetContent(RootOverlay);
	}
}
