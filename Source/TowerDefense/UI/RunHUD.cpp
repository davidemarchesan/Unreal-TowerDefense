// Fill out your copyright notice in the Description page of Project Settings.


#include "RunHUD.h"

#include "GameStyle.h"
#include "Components/ToolbarWidget.h"
#include "Components/TopBarStat.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/Enums/RunPhase.h"

#include "TowerDefense/PlayerControllers/RunPlayerController.h"
#include "TowerDefense/UI/Components/ButtonInputWidget.h"
#include "TowerDefense/UI/Components/ButtonPrimaryWidget.h"

#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/GameStates/RunGameState.h"

#include "Widgets/SOverlay.h"

void ARunHUD::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("HUD: BEGINPLAY"));

	// Getting game components
	GameMode = Cast<ARunGameMode>(GetWorld()->GetAuthGameMode());
	GameState = GetWorld()->GetGameState<ARunGameState>();
	PlayerController = Cast<ARunPlayerController>(GetOwningPlayerController());

	InitializeDelegateSubscribers();

	InitializeOverlays();

	InitializeHUDVariables();
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

void ARunHUD::OnPlayerHealthChange(float PlayerHealth)
{
	if (PlayerHealthStat)
	{
		FNumberFormattingOptions FormattingOptions;
		FormattingOptions.SetMaximumFractionalDigits(0);

		PlayerHealthStat->SetText(FText::AsNumber(PlayerHealth, &FormattingOptions));
	}
}

void ARunHUD::OnPlayerCoinsChange(float PlayerCoins)
{
	if (PlayerCoinsStat)
	{
		FNumberFormattingOptions FormattingOptions;
		FormattingOptions.SetMaximumFractionalDigits(0);

		PlayerCoinsStat->SetText(FText::AsNumber(PlayerCoins, &FormattingOptions));
	}
}

void ARunHUD::OnPlayerPointsChange(float PlayerPoints)
{
	if (PlayerPointsStat)
	{
		FNumberFormattingOptions FormattingOptions;
		FormattingOptions.SetMaximumFractionalDigits(0);

		PlayerPointsStat->SetText(FText::AsNumber(PlayerPoints, &FormattingOptions));
	}
}

FReply ARunHUD::OnSkipSetupPhase()
{
	if (PlayerController)
	{
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
		CreateToolBarOverlay(RootOverlay);

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

void ARunHUD::InitializeHUDVariables()
{
	if (GameState)
	{
		OnPlayerHealthChange(GameState->GetPlayerHealth());
		OnPlayerCoinsChange(GameState->GetPlayerCoins());
		OnPlayerPointsChange(GameState->GetPlayerPoints());
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
	           .Padding(FMargin(20.f))

	[

		SNew(SBorder)
		.BorderImage(
			new FSlateRoundedBoxBrush(FLinearColor::White, 24.f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("TowerDefense.Color.Gunmetal"))
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
					SAssignNew(PlayerHealthStat, STopBarStat)
					.Icon(FIconData("TowerDefense.Icons.Heart", "TowerDefense.Color.Beige", StatBoxIconWidth))
					.Text(FTextData(FText::FromString("0"), "TowerDefense.Color.Beige", 23.f))
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.f, 0.f, StatBoxSpacing, 0.f))
				.MinWidth(StatBoxWidth)
				.MaxWidth(StatBoxWidth)
				[
					SAssignNew(PlayerPointsStat, STopBarStat)
					.Icon(FIconData("TowerDefense.Icons.Star", "TowerDefense.Color.Beige", StatBoxIconWidth))
					.Text(FTextData(FText::FromString("0"), "TowerDefense.Color.Beige", 23.f))
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.f, 0.f, StatBoxSpacing, 0.f))
				.MinWidth(StatBoxWidth)
				.MaxWidth(StatBoxWidth)
				[
					SAssignNew(PlayerCoinsStat, STopBarStat)
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
						.Text(FText::FromString("SKIP"))
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.sm"))
					]
				]
			]


		]


	];
}

void ARunHUD::CreateToolBarOverlay(const TSharedRef<SOverlay>& RootOverlay)
{
	if (!PlayerController || !GameMode)
	{
		return;
	}

	const float ItemOutPadding = 5.f;
	const float ItemInPadding = 10.f;
	const float ItemWidth = 120.f;

	// Building menu
	BottomBar = SNew(SHorizontalBox);

	UDataTable* TurretDataTable = GameMode->TurretDataTable;
	TArray<FName> RowNames = TurretDataTable->GetRowNames();

	// for (const FName& RowName : RowNames)

	if (PlayerController->ToolbarSlots.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("pc has no toolbars"));
		return;
	}

	for (const FToolbarSlot& Slot : PlayerController->ToolbarSlots)
	{
		BottomBar->AddSlot()
		         .AutoWidth()
		         .Padding(ItemOutPadding, 0.f)
		[

			SNew(SBox)
			.WidthOverride(ItemWidth)
			.HeightOverride(ItemWidth)
			[

				SNew(SBorder)
				.Padding(10.f)
				.BorderImage(
					new FSlateRoundedBoxBrush(FLinearColor::White, 24.f))
				.BorderBackgroundColor(FGameStyle::Get().GetColor("TowerDefense.Color.Gunmetal"))
				[

					SNew(SOverlay)

					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text(Slot.Name)
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.sm"))
						.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
					]

					+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Bottom)
					[
						SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text(FText::AsNumber(Slot.Key))
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.xs"))
						.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
					]

					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Bottom)
					[
						SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text(FText::AsNumber(Slot.Price))
						.Font(FGameStyle::Get().GetFontStyle("TowerDefense.Font.Bold.xs"))
						.ColorAndOpacity(FGameStyle::Get().GetColor("TowerDefense.Color.Beige"))
					]

				]

			]

		];
	}

	RootOverlay->AddSlot()
	           .HAlign(HAlign_Center)
	           .VAlign(VAlign_Bottom)
	           .Padding(FMargin(20.f))

	[

		SNew(SVerticalBox)
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SToolbarWidget)
			.Slots(PlayerController->ToolbarSlots)
		]

		+ SVerticalBox::Slot()
		[
			SNew(STextBlock)
			.Justification(ETextJustify::Center)
			.Text(FText::FromString(TEXT("Loading")))
		]

		// BottomBar.ToSharedRef()


	];
}

void ARunHUD::InitializeDelegateSubscribers()
{
	if (GameMode)
	{
		GameMode->OnLevelReady.AddDynamic(this, &ARunHUD::OnLevelReady);
	}

	if (GameState)
	{
		GameState->OnPhaseStart.AddDynamic(this, &ARunHUD::OnPhaseStart);
		GameState->OnTimerUpdate.AddDynamic(this, &ARunHUD::OnTimerUpdate);

		GameState->OnPlayerHealthChange.AddDynamic(this, &ARunHUD::OnPlayerHealthChange);
		GameState->OnPlayerCoinsChange.AddDynamic(this, &ARunHUD::OnPlayerCoinsChange);
		GameState->OnPlayerPointsChange.AddDynamic(this, &ARunHUD::OnPlayerPointsChange);
	}
}

void ARunHUD::OnLevelReady()
{
	// UE_LOG(LogTemp, Warning, TEXT("HUD: Game is ready!"));
	if (LoadingScreen)
	{
		LoadingScreen->SetVisibility(EVisibility::Collapsed);
	}
}

void ARunHUD::OnPhaseStart(ERunPhase NewPhase)
{
	switch (NewPhase)
	{
	case ERunPhase::Setup:
		PrepareForSetupPhase();
		break;

	case ERunPhase::Defense:
		PrepareForDefensePhase();
		break;
	}
}

void ARunHUD::PrepareForSetupPhase()
{
	if (!NextWaveHBox || !NextWaveSkipButton || !NextWaveTimerTextBlock)
	{
		return;
	}

	NextWaveTimerTextBlock->SetVisibility(EVisibility::Visible);
	NextWaveSkipButton->SetVisibility(EVisibility::Visible);
	NextWaveHBox->SetVisibility(EVisibility::Visible);

	BottomBar->SetVisibility(EVisibility::Visible);
}

void ARunHUD::PrepareForDefensePhase()
{
	if (!NextWaveHBox)
	{
		return;
	}

	NextWaveHBox->SetVisibility(EVisibility::Collapsed);
	BottomBar->SetVisibility(EVisibility::Collapsed);
}
