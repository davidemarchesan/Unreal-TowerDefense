// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wall.h"
#include "TowerDefense/Enums/PreviewWallState.h"
#include "PreviewWall.generated.h"

class UMaterialInstanceDynamic;


/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API APreviewWall : public AWall
{
	GENERATED_BODY()

public:

	APreviewWall();

	void SetPreviewState(EPreviewWallState State);

protected:

	virtual void BeginPlay() override;

private:

	// Preview
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterialIstance;

	UPROPERTY(EditAnywhere, Category = "Preview")
	FLinearColor ValidPreviewColor;

	UPROPERTY(EditAnywhere, Category = "Preview")
	FLinearColor InvalidPreviewColor;

	UPROPERTY(EditAnywhere, Category = "Preview")
	float PreviewIntensity = 0.f;

	EPreviewWallState PreviewState;
	
};
