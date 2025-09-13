// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LayoutEditorPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraInputConfig;
class AGameCamera;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ALayoutEditorPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:

	// Pawn
	AGameCamera* CameraPawn;

	// Input Mapping Contexts
	/*UPROPERTY(EditAnywhere, Category = "Input")
	UCameraInputConfig* LayoutEditorInputConfig;*/

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* LayoutEditorMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UCameraInputConfig* CameraInputConfig;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* CameraMappingContext;

	// Input functions
	void MoveCamera(const FInputActionValue& Value);

	void RotateCamera(const FInputActionValue& Value);

	void ZoomCamera(const FInputActionValue& Value);
	
};
