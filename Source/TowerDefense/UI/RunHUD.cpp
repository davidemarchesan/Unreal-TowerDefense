// Fill out your copyright notice in the Description page of Project Settings.


#include "RunHUD.h"

#include "GameStyle.h"
#include "Components/TopBarStat.h"
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

}

void ARunHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ARunHUD::ToggleBuildMode(bool _bIsBuildMode)
{
	bIsBuildMode = _bIsBuildMode;

}

void ARunHUD::OnTimerUpdate(int32 Time)
{

	if (!NextWaveHBox || !NextWaveSkipButton || !NextWaveTimerTextBlock)
	{
		return;
	}
	
	if (Time <= 0)
	{
		NextWaveHBox->SetVisibility(EVisibility::Collapsed);
	}
	else if (Time <= 3)
	{
		NextWaveSkipButton->SetVisibility(EVisibility::Hidden);
		NextWaveTimerTextBlock->SetColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Yellow"));
	}

	NextWaveTimerTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%d"), Time)));
	
}

FReply ARunHUD::OnSkipSetupPhase()
{
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("ARunPlayerController::OnSkipSetupPhase"));
		PlayerController->SkipSetupPhase();

		return FReply::Handled();
	}
	
	return FReply::Unhandled();
}

void ARunHUD::InitializeOverlays()
{
	if (GEngine && GEngine->GameViewport)
	{
		const TSharedRef<SOverlay> RootOverlay = SNew(SOverlay);

		// Loading overlay
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
				+ SVerticalBox::Slot()
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

		CreateTopBarOverlay(RootOverlay);
		
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

		GEngine->GameViewport->AddViewportWidgetContent(RootOverlay);

		if (GameMode->IsLevelLoaded())
		{
			OnLevelReady();
		}
	}
}

void ARunHUD::CreateTopBarOverlay(const TSharedRef<SOverlay>& RootOverlay)
{
	const float StatBoxWidth = 175.f;
	const float StatBoxSpacing = 20.f;

	const float StatBoxIconWidth = 32.f;

	// Top bar
	RootOverlay->AddSlot()
	           .HAlign(HAlign_Center)
	           .VAlign(VAlign_Top)

	[

		SNew(SBorder)
		.BorderImage(
			new FSlateRoundedBoxBrush(FLinearColor::White, FVector4(0, 0, 12, 12)))
		.BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.5f))
		.Padding(FMargin(20))
		[

			SNew(SVerticalBox)

			// Stats
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.f, 0.f, StatBoxSpacing, 0.f))
				.VAlign(VAlign_Center)
				.MinWidth(StatBoxWidth)
				.MaxWidth(StatBoxWidth)
				[
					SNew(STopBarStat)
					.Icon(FIconData("TowerDefense.Icons.Heart", "TowerDefense.Color.Beige", StatBoxIconWidth))
					.Text(FTextData(FText::FromString("0"), "TowerDefense.Color.Beige", 23.f))
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.f, 0.f, StatBoxSpacing, 0.f))
				.MinWidth(StatBoxWidth)
				.MaxWidth(StatBoxWidth)
				[
					SNew(STopBarStat)
					.Icon(FIconData("TowerDefense.Icons.Star", "TowerDefense.Color.Beige", StatBoxIconWidth))
					.Text(FTextData(FText::FromString("0"), "TowerDefense.Color.Beige", 23.f))
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.f, 0.f, StatBoxSpacing, 0.f))
				.MinWidth(StatBoxWidth)
				.MaxWidth(StatBoxWidth)
				[
					SNew(STopBarStat)
					.Icon(FIconData("TowerDefense.Icons.Coins", "TowerDefense.Color.Beige", StatBoxIconWidth))
					.Text(FTextData(FText::FromString("0"), "TowerDefense.Color.Beige", 23.f))
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.f, 0.f, StatBoxSpacing, 0.f))
				.MinWidth(StatBoxWidth)
				.MaxWidth(StatBoxWidth)
				[
					SNew(STopBarStat)
					.Icon(FIconData("TowerDefense.Icons.Meteor", "TowerDefense.Color.Beige", StatBoxIconWidth))
					.Text(FTextData(FText::FromString("0"), "TowerDefense.Color.Beige", 23.f))
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.f, 0.f, StatBoxSpacing, 0.f))
				.MinWidth(StatBoxWidth)
				.MaxWidth(StatBoxWidth)
				[
					SNew(STopBarStat)
					.Icon(FIconData("TowerDefense.Icons.Skull", "TowerDefense.Color.Beige", StatBoxIconWidth))
					.Text(FTextData(FText::FromString("0"), "TowerDefense.Color.Beige", 23.f))
				]
			]

			// Next wave timer and skip button
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(FMargin(0, 20.f, 0, 0))
			[
				SAssignNew(NextWaveHBox, SHorizontalBox)
				.Visibility(EVisibility::Visible)

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				[

					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					.Padding(FMargin(0, 0, 10.f, 0))
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(FText::FromString("Next wave in:"))
						.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.md"))
					]

					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SAssignNew(NextWaveTimerTextBlock, STextBlock)
						.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.lg"))
					]


				]

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				[
					
					SAssignNew(NextWaveSkipButton, SButton)
					.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("TowerDefense.Button.Yellow"))
					.OnClicked(FOnClicked::CreateUObject(this, &ARunHUD::OnSkipSetupPhase))
					[
						SNew(STextBlock)
						.Text(FText::FromString("Skip"))
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.sm"))
					]
				]
			]


		]


	];
}

void ARunHUD::InitializeDelegateSubscribers()
{
	if (GameMode)
	{
		GameMode->OnLevelReady.AddDynamic(this, &ARunHUD::OnLevelReady);
	}

	if (GameSate)
	{
		GameSate->OnPhaseStart.AddDynamic(this, &ARunHUD::OnPhaseStart);
		GameSate->OnTimerUpdate.AddDynamic(this, &ARunHUD::OnTimerUpdate);
	}
}

void ARunHUD::OnLevelReady()
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
