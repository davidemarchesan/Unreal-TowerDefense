// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetHealthPercent(float Percent);

private:

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;
	
};
