// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LayoutEditorInputConfig.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ULayoutEditorInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_PrimaryAction;
	
};
