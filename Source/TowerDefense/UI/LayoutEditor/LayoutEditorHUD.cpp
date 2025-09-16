// Fill out your copyright notice in the Description page of Project Settings.


#include "LayoutEditorHUD.h"

#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "Widgets/SWeakWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/SViewport.h"

#include "TowerDefense/UI/Components/ButtonPrimaryWidget.h"

void ALayoutEditorHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{

		UE_LOG(LogTemp, Warning, TEXT("Adding HUD"));

		TSharedRef<SOverlay> RootOverlay = SNew(SOverlay);

		RootOverlay->AddSlot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Bottom)
		.Padding(FMargin(20))
		[
			SNew(SButtonPrimaryWidget)
				.ButtonText(FText::FromString("Save"))
		];

		GEngine->GameViewport->AddViewportWidgetContent(RootOverlay);
		/*GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(RootOverlay.ToSharedRef())
		);*/
	}
}

void ALayoutEditorHUD::DrawHUD()
{
	Super::DrawHUD();
}
