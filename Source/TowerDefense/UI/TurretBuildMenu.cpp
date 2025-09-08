// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBuildMenu.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/Engine.h"
#include "GameHUD.h"

void STurretBuildMenu::Construct(const FArguments& InArgs)
{

	OwnerHUD = InArgs._OwnerHUD;

	ChildSlot
		[
			SNew(SBorder)
				.Padding(10)
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SButton)
								.Text(FText::FromString("Base"))
								.OnClicked(this, &STurretBuildMenu::OnBuildTurret)
						]
				]
		];
}

FReply STurretBuildMenu::OnBuildTurret()
{
	if (OwnerHUD) OwnerHUD->RequestBuildTurret();
	UE_LOG(LogTemp, Warning, TEXT("slate: click on button base"));

	return FReply::Handled();
}
