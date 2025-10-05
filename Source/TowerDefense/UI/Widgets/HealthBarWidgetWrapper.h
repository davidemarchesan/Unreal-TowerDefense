// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidgetWrapper.generated.h"

class SHealthBarWidget;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UHealthBarWidgetWrapper : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual TSharedRef<SWidget> RebuildWidget() override;

	void SetHealthPercent(float InPercent);

private:
	TSharedPtr<SHealthBarWidget> HealthBarWidget;
};
