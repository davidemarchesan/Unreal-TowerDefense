// Fill out your copyright notice in the Description page of Project Settings.


#include "PreviewWall.h"
#include "Materials/MaterialInstanceDynamic.h"

APreviewWall::APreviewWall() : Super()
{
	PreviewState = EPreviewWallState::None;
}

void APreviewWall::BeginPlay()
{
	Super::BeginPlay();

	// Crea il materiale dinamico per la mesh
	if (Mesh && Mesh->GetMaterial(0))
	{
		DynamicMaterialIstance = Mesh->CreateDynamicMaterialInstance(0, Mesh->GetMaterial(0));
	}
}

void APreviewWall::SetPreviewState(EPreviewWallState State)
{

	switch (State)
	{
	case EPreviewWallState::None:
		DynamicMaterialIstance->SetScalarParameterValue(TEXT("PreviewIntensity"), 0.f);
		break;
	case EPreviewWallState::Valid:
		DynamicMaterialIstance->SetVectorParameterValue(TEXT("PreviewColor"), ValidPreviewColor);
		DynamicMaterialIstance->SetScalarParameterValue(TEXT("PreviewIntensity"), PreviewIntensity);
		break;
	case EPreviewWallState::Invalid:
		DynamicMaterialIstance->SetVectorParameterValue(TEXT("PreviewColor"), InvalidPreviewColor);
		DynamicMaterialIstance->SetScalarParameterValue(TEXT("PreviewIntensity"), PreviewIntensity);
		break;
	default:
		DynamicMaterialIstance->SetScalarParameterValue(TEXT("PreviewIntensity"), 0.f);
		break;
	}
}