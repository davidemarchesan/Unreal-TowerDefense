// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "Widgets/SWeakWidget.h"
#include "Widgets/SViewport.h"

#include "TurretBuildMenu.h"

#include "TowerDefense/TopDownPlayerController.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		SAssignNew(BuildMenu, STurretBuildMenu)
			.OwnerHUD(this);

		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(BuildMenu.ToSharedRef())
		);
	}

	PC = Cast<ATopDownPlayerController>(GetOwningPlayerController());
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHUD::RequestBuildTurret()
{
	UE_LOG(LogTemp, Warning, TEXT("HUD: requesting building a tower"));
	if (PC)
	{
		PC->RequestBuildTurret();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD: PC is not valid"));
	}
}