// Fill out your copyright notice in the Description page of Project Settings.


#include "LayoutEditorHUD.h"

#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "TowerDefense/UI/Components/ButtonInputWidget.h"

#include "Widgets/SWeakWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/SViewport.h"

#include "TowerDefense/UI/Components/ButtonPrimaryWidget.h"

void ALayoutEditorHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{

		const TSharedRef<SOverlay> RootOverlay = SNew(SOverlay);

		RootOverlay->AddSlot()
		           .HAlign(HAlign_Right)
		           .VAlign(VAlign_Bottom)
		           .Padding(FMargin(20))
		[
			// SNew(SButtonPrimaryWidget)
			// .ButtonText(FText::FromString("Save"))

			SNew(SButtonInputWidget)
			.InputText(FText::FromString("B"))
			.ButtonText(FText::FromString("BUILD"))
		];

		GEngine->GameViewport->AddViewportWidgetContent(RootOverlay);
	}
}

void ALayoutEditorHUD::DrawHUD()
{
	Super::DrawHUD();
}
