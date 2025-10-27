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

	// Toolbar slots
	TArray<FToolbarSlot> ToolbarSlots;	
	TArray<FToolbarSlot> TurretsToolbarSlots;

private:

	void AddMappingContexts();

	void InitializeDelegates();
	
	// Pawn
	AGameCamera* CameraPawn;

	// Game components
	ARunGameMode* GameMode;
	ARunGameState* GameState;

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

	void DeprojectPointer();

	// Input functions - Camera
	void MoveCamera(const FInputActionValue& Value);

	void RotateCamera(const FInputActionValue& Value);

	void ZoomCamera(const FInputActionValue& Value);

	// Input functions - Toolbar
	TArray<FToolbarSlot>* ActiveToolbar = nullptr;
	void OnToolbarSelectSlot(const int32 Slot);
	void OnToolbarSelectSlot1();
	void OnToolbarSelectSlot2();
	void OnToolbarSelectSlot3();
	void OnToolbarSelectSlot4();
	void OnToolbarSelectSlot5();
	void OnToolbarSelectSlot6();

	
	
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
	
};
