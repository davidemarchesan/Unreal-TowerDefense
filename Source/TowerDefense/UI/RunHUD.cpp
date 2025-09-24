// Fill out your copyright notice in the Description page of Project Settings.


#include "RunHUD.h"

#include "GameStyle.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "TowerDefense/GameModes/RunGameMode.h"

#include "TowerDefense/PlayerControllers/RunPlayerController.h"
#include "TowerDefense/UI/Components/ButtonInputWidget.h"
#include "TowerDefense/UI/Components/ButtonPrimaryWidget.h"

#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/GameStates/RunGameState.h"

#include "Widgets/SOverlay.h"

void ARunHUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("HUD: BEGINPLAY"));

	// Getting game components
	GameMode = Cast<ARunGameMode>(GetWorld()->GetAuthGameMode());
	GameSate = GetWorld()->GetGameState<ARunGameState>();
	PlayerController = Cast<ARunPlayerController>(GetOwningPlayerController());

	InitializeDelegateSubscribers();

	InitializeOverlays();

	UpdateComponentsOnBuildMode();
}

void ARunHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ARunHUD::ToggleBuildMode(bool _bIsBuildMode)
{
	bIsBuildMode = _bIsBuildMode;

	UpdateComponentsOnBuildMode();
}

void ARunHUD::InitializeOverlays()
{
	if (GEngine && GEngine->GameViewport)
	{
		const TSharedRef<SOverlay> RootOverlay = SNew(SOverlay);

		RootOverlay->AddSlot()
		           .HAlign(HAlign_Fill)
		           .VAlign(VAlign_Fill)
		[
			SAssignNew(LoadingScreen, SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
			.BorderBackgroundColor(FGameStyle::Get().GetColor("TowerDefense.Color.Gunmetal"))
			[

				SNew(SVerticalBox)

				// Loading
				+SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SBox)
					.Padding(FMargin(0, 20))
					[

						SNew(STextBlock)
						.Text(FText::FromString("Loading"))
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold"))
						.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))

					]
				]

			]
		];

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

		// Save overlay
		RootOverlay->AddSlot()
		           .HAlign(HAlign_Right)
		           .VAlign(VAlign_Bottom)
		           .Padding(FMargin(20))
		[

			SAssignNew(SaveLayoutBox, SBox)
			[
				SNew(SButtonPrimaryWidget)
				.ButtonText(FText::FromString("SAVE LAYOUT"))
				.OnClicked(FOnClicked::CreateUObject(this, &ARunHUD::OnSaveLayout))
			]

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
						.OnClicked(FOnClicked::CreateUObject(this, &ARunHUD::OnToggleBuildMode))
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
						.OnClicked(FOnClicked::CreateUObject(this, &ARunHUD::OnToggleBuildMode))
					]

				]

			]


		];

		GEngine->GameViewport->AddViewportWidgetContent(RootOverlay);

		if (GameMode->IsLevelLoaded())
		{
			OnGameReady();
		}
	}
}

void ARunHUD::InitializeDelegateSubscribers()
{
	if (GameMode)
	{
		GameMode->OnGameReady.AddDynamic(this, &ARunHUD::OnGameReady);
	}

	if (GameSate)
	{
		GameSate->OnPhaseStart.AddDynamic(this, &ARunHUD::OnPhaseStart);
	}
}

void ARunHUD::OnGameReady()
{
	UE_LOG(LogTemp, Warning, TEXT("HUD: Game is ready!"));
	if (LoadingScreen)
	{
		LoadingScreen->SetVisibility(EVisibility::Collapsed);
	}
}

void ARunHUD::OnPhaseStart()
{
	UE_LOG(LogTemp, Warning, TEXT("arunhud: onphasestart"));
}

FReply ARunHUD::OnToggleBuildMode()
{
	if (PlayerController)
	{
		PlayerController->ToggleBuildMode();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply ARunHUD::OnSaveLayout()
{
	if (PlayerController)
	{
		// PlayerController->SaveLayout();
	}

	return FReply::Unhandled();
}

void ARunHUD::UpdateComponentsOnBuildMode()
{
	// BuildModeBorder->SetVisibility(bIsBuildMode ? EVisibility::Visible : EVisibility::Collapsed);
	//
	// StandardModeBox->SetVisibility(!bIsBuildMode ? EVisibility::Visible : EVisibility::Collapsed);
	// BuildModeBox->SetVisibility(bIsBuildMode ? EVisibility::Visible : EVisibility::Collapsed);
	//
	// SaveLayoutBox->SetVisibility(!bIsBuildMode ? EVisibility::Visible : EVisibility::Collapsed);
}
