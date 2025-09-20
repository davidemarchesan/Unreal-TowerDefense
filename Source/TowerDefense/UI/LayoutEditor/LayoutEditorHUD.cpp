// Fill out your copyright notice in the Description page of Project Settings.


#include "LayoutEditorHUD.h"

#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "TowerDefense/PlayerControllers/LayoutEditorPlayerController.h"
#include "TowerDefense/UI/Components/ButtonInputWidget.h"

#include "Widgets/SWeakWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/SViewport.h"

#include "TowerDefense/UI/Components/ButtonPrimaryWidget.h"

void ALayoutEditorHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ALayoutEditorPlayerController>(GetOwningPlayerController());

	if (GEngine && GEngine->GameViewport)
	{
		const TSharedRef<SOverlay> RootOverlay = SNew(SOverlay);

		// Build Mode overlay
		RootOverlay->AddSlot()
		           .HAlign(HAlign_Fill)
		           .VAlign(VAlign_Fill)
		[

			SAssignNew(BuildModeBorder, SBorder)
			.BorderImage(new FSlateRoundedBoxBrush(
				FLinearColor::Transparent,
				0.f,
				FLinearColor::Yellow, 10.f))
			.Visibility(EVisibility::Hidden)
		];

		// Commands overlay
		RootOverlay->AddSlot()
		           .HAlign(HAlign_Fill)
		           .VAlign(VAlign_Bottom)
		           .Padding(FMargin(20))
		[

			SNew(SHorizontalBox)

			// Standard Mode container
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			[

				SAssignNew(StandardModeBox, SBox)
				[

					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Center)
					.Padding(FMargin(10.f, 0))
					[
						SNew(SButtonInputWidget)
						.InputText(FText::FromString("B"))
						.ButtonText(FText::FromString("ENTER BUILD MODE"))
						.OnClicked(FOnClicked::CreateUObject(this, &ALayoutEditorHUD::OnToggleBuildMode))
					]

				]

			]

			// Build Mode container
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			[

				SAssignNew(BuildModeBox, SBox)
				[

					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Center)
					.Padding(FMargin(10.f, 0))
					[
						SNew(SButtonInputWidget)
						.InputText(FText::FromString("B"))
						.ButtonText(FText::FromString("EXIT BUILD MODE"))
						.OnClicked(FOnClicked::CreateUObject(this, &ALayoutEditorHUD::OnToggleBuildMode))
					]

				]

			]


		];

		GEngine->GameViewport->AddViewportWidgetContent(RootOverlay);
	}

	UpdateComponentsOnBuildMode();
}

void ALayoutEditorHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ALayoutEditorHUD::ToggleBuildMode(bool _bIsBuildMode)
{
	bIsBuildMode = _bIsBuildMode;

	UpdateComponentsOnBuildMode();
}

FReply ALayoutEditorHUD::OnToggleBuildMode()
{
	if (PlayerController)
	{
		PlayerController->ToggleBuildMode();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void ALayoutEditorHUD::UpdateComponentsOnBuildMode()
{
	BuildModeBorder->SetVisibility(bIsBuildMode ? EVisibility::Visible : EVisibility::Collapsed);

	StandardModeBox->SetVisibility(!bIsBuildMode ? EVisibility::Visible : EVisibility::Collapsed);
	BuildModeBox->SetVisibility(bIsBuildMode ? EVisibility::Visible : EVisibility::Collapsed);
}
