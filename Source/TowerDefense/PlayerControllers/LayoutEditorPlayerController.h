// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LayoutEditorPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ULayoutEditorInputConfig;
class UCameraInputConfig;
class AGameCamera;
class ALayoutGrid;
class ALayoutEditorHUD;
class UTowerDefenseGameInstance;
class ALayoutEditorGameMode;
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

public: 

	virtual void Tick(float DeltaTime) override;

	// Input functions
	void ToggleBuildMode();

	void SaveLayout();

private:

	// Pawn
	AGameCamera* CameraPawn;

	// GameMode
	ALayoutEditorGameMode* GameMode;

	// GameInstance
	UTowerDefenseGameInstance* GameInstance;

	// HUD
	ALayoutEditorHUD* HUD;

	// Input Mapping Contexts
	UPROPERTY(EditAnywhere, Category = "Input")
	ULayoutEditorInputConfig* LayoutEditorInputConfig;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* LayoutEditorMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UCameraInputConfig* CameraInputConfig;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* CameraMappingContext;

	// Input functions
	void PrimaryAction();

	void MoveCamera(const FInputActionValue& Value);

	void RotateCamera(const FInputActionValue& Value);

	void ZoomCamera(const FInputActionValue& Value);

	// Building
	ALayoutGrid* LayoutGrid;

	void GetLayoutGrid();

	UFUNCTION()
	void OnGridInitialized();

	void DeprojectMouse();

	bool bIsBuildMode = false;

	bool IsBuildModeActive() const { return bIsBuildMode; }
	
};
