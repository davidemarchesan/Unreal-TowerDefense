// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolbarSlot.h"
#include "GameFramework/PlayerController.h"
#include "RunPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class URunInputConfig;
class UCameraInputConfig;
class AGameCamera;
class ALayoutGrid;
class ARunHUD;
class UTowerDefenseGameInstance;
class ARunGameMode;
class ARunGameState;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ARunPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	void SkipSetupPhase();

	TArray<FToolbarSlot> ToolbarSlots;

private:
	
	// Pawn
	AGameCamera* CameraPawn;

	// Game components
	ARunGameMode* GameMode;
	ARunGameState* GameState;
	UTowerDefenseGameInstance* GameInstance;

	// HUD
	ARunHUD* HUD;

	// Input Mapping Contexts
	UPROPERTY(EditAnywhere, Category = "Input")
	URunInputConfig* RunInputConfig;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* RunMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UCameraInputConfig* CameraInputConfig;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* CameraMappingContext;

	// Toolbar slots
	void InitializeToolbarSlots();
	
	// Input functions
	void PrimaryAction();

	void MoveCamera(const FInputActionValue& Value);

	void RotateCamera(const FInputActionValue& Value);

	void ZoomCamera(const FInputActionValue& Value);
	
	void RequestToggleBuildWallMode();
	bool bIsBuildWallMode = false;

	UFUNCTION()
	void OnBuildWallModeToggle(bool _bIsBuildWallMode);

	void RequestToggleBuildTurretMode_Slot2();

	void RequestToggleBuildTurretMode_Slot3();

	void RequestToggleBuildTurretMode(const int32 SlotNumber);
	bool bIsBuildTurretMode = false;

	UFUNCTION()
	void OnBuildTurretModeToggle(bool _bIsBuildTurretMode);

	void DeprojectPointer();


};
