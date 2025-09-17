// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonPrimaryWidget.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/Engine.h"

void SButtonPrimaryWidget::Construct(const FArguments& InArgs)
{
	ButtonText = InArgs._ButtonText;

	ChildSlot
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::Yellow)
			[
				SNew(SButton)
				.OnClicked(this, &SButtonPrimaryWidget::OnButtonClick)
				.ForegroundColor(FLinearColor::Yellow)
				[
					SNew(STextBlock)
					.Text(ButtonText)
					.ColorAndOpacity(FLinearColor::Black)
					.Justification(ETextJustify::Center)
				]
			]
		];
}

FReply SButtonPrimaryWidget::OnButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Primary button"));
	return FReply::Handled();
}