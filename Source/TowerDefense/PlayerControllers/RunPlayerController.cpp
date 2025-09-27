// Fill out your copyright notice in the Description page of Project Settings.


#include "RunPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TowerDefense/Input/Config/LayoutEditorInputConfig.h"
#include "TowerDefense/Input/Config/CameraInputConfig.h"
#include "InputActionValue.h"
#include "TowerDefense/GameCamera.h"
#include "TowerDefense/LayoutGrid.h"
#include "EngineUtils.h"
#include "TowerDefense/TowerDefenseGameInstance.h"
#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/GameStates/RunGameState.h"
#include "TowerDefense/UI/RunHUD.h"
#include "TowerDefense/Walls/Wall.h"

void ARunPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>())
		{
			if (LayoutEditorMappingContext)
			{
				InputSystem->AddMappingContext(LayoutEditorMappingContext, 0);
			}
			if (CameraMappingContext)
			{
				InputSystem->AddMappingContext(CameraMappingContext, 1);
			}
		}
	}

	HUD = Cast<ARunHUD>(GetHUD());

	GameMode = Cast<ARunGameMode>(GetWorld()->GetAuthGameMode());

	GameState = Cast<ARunGameState>(GetWorld()->GetGameState());

	GameInstance = Cast<UTowerDefenseGameInstance>(GetGameInstance());

	CameraPawn = Cast<AGameCamera>(GetPawn());
	if (GameMode && CameraPawn)
	{
		CameraPawn->SetActorLocation(GameMode->GetCameraStartLocation());
		CameraPawn->SetActorRotation(FRotator::ZeroRotator);
	}
}

void ARunPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (LayoutEditorInputConfig)
		{
			EnhancedInput->BindAction(LayoutEditorInputConfig->IA_PrimaryAction, ETriggerEvent::Triggered, this,
			                          &ARunPlayerController::PrimaryAction);

			EnhancedInput->BindAction(LayoutEditorInputConfig->IA_EnterBuildMode, ETriggerEvent::Triggered, this,
			                          &ARunPlayerController::ToggleBuildMode);
		}

		if (CameraInputConfig)
		{
			EnhancedInput->BindAction(CameraInputConfig->IA_MoveCamera, ETriggerEvent::Triggered, this,
			                          &ARunPlayerController::MoveCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_MoveCamera, ETriggerEvent::Completed, this,
			                          &ARunPlayerController::MoveCamera);

			EnhancedInput->BindAction(CameraInputConfig->IA_RotateCamera, ETriggerEvent::Triggered, this,
			                          &ARunPlayerController::RotateCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_RotateCamera, ETriggerEvent::Completed, this,
			                          &ARunPlayerController::RotateCamera);

			EnhancedInput->BindAction(CameraInputConfig->IA_ZoomCamera, ETriggerEvent::Triggered, this,
			                          &ARunPlayerController::ZoomCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_ZoomCamera, ETriggerEvent::Completed, this,
			                          &ARunPlayerController::ZoomCamera);
		}
	}
}

void ARunPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeprojectMouse();
}

void ARunPlayerController::PrimaryAction()
{
	// if (IsBuildModeActive() && LayoutGrid && GameMode)
	// {
	// 	FHitResult Hit;
	// 	if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
	// 	{
	// 		if (Hit.GetActor()->ActorHasTag(FName("TurretWall")))
	// 		{
	// 			if (const AWall* TurretWall = Cast<AWall>(Hit.GetActor()))
	// 			{
	// 				LayoutGrid->RequestWallRemoval(TurretWall->Col, TurretWall->Row);
	// 				// int32 CurrentTurretWalls = GameMode->RegisterTurretWallRemoval();
	// 			}
	// 		}
	// 		else if (Hit.GetActor()->ActorHasTag(FName("LayoutGrid")))
	// 		{
	// 			// if (GameMode->CanPlaceTurretWall())
	// 			// {
	// 			// 	if (LayoutGrid->RequestWallBuild(Hit.Location))
	// 			// 	{
	// 			// 		int32 CurrentTurretWalls = GameMode->RegisterTurretWallPlacement();
	// 			// 	}
	// 			// }
	// 		}
	// 	}
	// }
}

void ARunPlayerController::ToggleBuildMode()
{
	bIsBuildMode = !bIsBuildMode;
	if (HUD) HUD->ToggleBuildMode(bIsBuildMode);

	if (IsBuildModeActive() == false)
	{
		// LayoutGrid->RequestResetPreviewWall();
	}
}

void ARunPlayerController::SkipSetupPhase()
{
	if (GameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("ARunPlayerController::SkipSetupPhase"));
		GameState->SkipSetupPhase();
	}
}

void ARunPlayerController::MoveCamera(const FInputActionValue& Value)
{
	if (CameraPawn)
	{
		FVector2D InputValue = Value.Get<FVector2D>();
		CameraPawn->RequestMove(FVector2D(InputValue.Y, InputValue.X));
	}
}

void ARunPlayerController::RotateCamera(const FInputActionValue& Value)
{
	if (CameraPawn)
	{
		float InputValue = Value.Get<float>();
		CameraPawn->RequestRotation(InputValue);
	}
}

void ARunPlayerController::ZoomCamera(const FInputActionValue& Value)
{
	if (CameraPawn)
	{
		float InputValue = Value.Get<float>();
		CameraPawn->RequestZoom(InputValue);
	}
}

void ARunPlayerController::DeprojectMouse()
{
	if (IsBuildModeActive() == false)
	{
		return;
	}

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
	{
		if (Hit.GetActor()->ActorHasTag(FName("TurretWall")))
		{
			// if (LayoutGrid)
			// {
			// 	LayoutGrid->RequestResetPreviewWall();
			// }
		}
		else if (Hit.GetActor()->ActorHasTag(FName("LayoutGrid")))
		{
			// if (GameMode && GameMode->CanPlaceTurretWall() && LayoutGrid)
			// {
			// 	LayoutGrid->RequestPreviewWall(Hit.Location);
			// }
		}
	}
}
