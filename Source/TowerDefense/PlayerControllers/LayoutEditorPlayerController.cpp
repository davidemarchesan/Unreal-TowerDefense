// Fill out your copyright notice in the Description page of Project Settings.


#include "LayoutEditorPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TowerDefense/Input/Config/LayoutEditorInputConfig.h"
#include "TowerDefense/Input/Config/CameraInputConfig.h"
#include "InputActionValue.h"
#include "TowerDefense/GameCamera.h"
#include "TowerDefense/LayoutGrid.h"
#include "EngineUtils.h"
#include "TowerDefense/TowerDefenseGameInstance.h"
#include "TowerDefense/GameModes/LayoutEditorGameMode.h"
#include "TowerDefense/UI/LayoutEditor/LayoutEditorHUD.h"
#include "TowerDefense/Walls/Wall.h"

void ALayoutEditorPlayerController::BeginPlay()
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

	CameraPawn = Cast<AGameCamera>(GetPawn());

	GetLayoutGrid();

	HUD = Cast<ALayoutEditorHUD>(GetHUD());

	GameMode = Cast<ALayoutEditorGameMode>(GetWorld()->GetAuthGameMode());

	GameInstance = Cast<UTowerDefenseGameInstance>(GetGameInstance());
}

void ALayoutEditorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (LayoutEditorInputConfig)
		{
			EnhancedInput->BindAction(LayoutEditorInputConfig->IA_PrimaryAction, ETriggerEvent::Triggered, this,
			                          &ALayoutEditorPlayerController::PrimaryAction);

			EnhancedInput->BindAction(LayoutEditorInputConfig->IA_EnterBuildMode, ETriggerEvent::Triggered, this,
			                          &ALayoutEditorPlayerController::ToggleBuildMode);
		}

		if (CameraInputConfig)
		{
			EnhancedInput->BindAction(CameraInputConfig->IA_MoveCamera, ETriggerEvent::Triggered, this,
			                          &ALayoutEditorPlayerController::MoveCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_MoveCamera, ETriggerEvent::Completed, this,
			                          &ALayoutEditorPlayerController::MoveCamera);

			EnhancedInput->BindAction(CameraInputConfig->IA_RotateCamera, ETriggerEvent::Triggered, this,
			                          &ALayoutEditorPlayerController::RotateCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_RotateCamera, ETriggerEvent::Completed, this,
			                          &ALayoutEditorPlayerController::RotateCamera);

			EnhancedInput->BindAction(CameraInputConfig->IA_ZoomCamera, ETriggerEvent::Triggered, this,
			                          &ALayoutEditorPlayerController::ZoomCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_ZoomCamera, ETriggerEvent::Completed, this,
			                          &ALayoutEditorPlayerController::ZoomCamera);
		}
	}
}

void ALayoutEditorPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeprojectMouse();
}

void ALayoutEditorPlayerController::PrimaryAction()
{
	if (IsBuildModeActive() && LayoutGrid && GameMode)
	{
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
		{
			if (Hit.GetActor()->ActorHasTag(FName("TurretWall")))
			{
				if (const AWall* TurretWall = Cast<AWall>(Hit.GetActor()))
				{
					LayoutGrid->RequestWallRemoval(TurretWall->Col, TurretWall->Row);
					int32 CurrentTurretWalls = GameMode->RegisterTurretWallRemoval();
				}
			}
			else if (Hit.GetActor()->ActorHasTag(FName("LayoutGrid")))
			{
				if (GameMode->CanPlaceTurretWall())
				{
					if (LayoutGrid->RequestWallBuild(Hit.Location))
					{
						int32 CurrentTurretWalls = GameMode->RegisterTurretWallPlacement();
					}
				}
			}
		}
	}
}

void ALayoutEditorPlayerController::ToggleBuildMode()
{
	bIsBuildMode = !bIsBuildMode;
	if (HUD) HUD->ToggleBuildMode(bIsBuildMode);

	if (IsBuildModeActive() == false && LayoutGrid)
	{
		LayoutGrid->RequestResetPreviewWall();
	}
}

void ALayoutEditorPlayerController::SaveLayout()
{
	if (LayoutGrid && GameInstance)
	{
		TArray<FIntPoint> GridLayout;
		// LayoutGrid->GetLayout(GridLayout);

		GameInstance->SaveGridLayout(GridLayout);
	}
}

void ALayoutEditorPlayerController::MoveCamera(const FInputActionValue& Value)
{
	if (CameraPawn)
	{
		FVector2D InputValue = Value.Get<FVector2D>();
		CameraPawn->RequestMove(FVector2D(InputValue.Y, InputValue.X));
	}
}

void ALayoutEditorPlayerController::RotateCamera(const FInputActionValue& Value)
{
	if (CameraPawn)
	{
		float InputValue = Value.Get<float>();
		CameraPawn->RequestRotation(InputValue);
	}
}

void ALayoutEditorPlayerController::ZoomCamera(const FInputActionValue& Value)
{
	if (CameraPawn)
	{
		float InputValue = Value.Get<float>();
		CameraPawn->RequestZoom(InputValue);
	}
}

void ALayoutEditorPlayerController::GetLayoutGrid()
{
	for (TActorIterator<ALayoutGrid> It(GetWorld()); It; ++It)
	{
		LayoutGrid = *It;

		if (LayoutGrid)
		{
			if (LayoutGrid->IsGridInitialized())
			{
				OnGridInitialized();
			}
			else
			{
				LayoutGrid->OnGridInitialized.AddDynamic(this, &ALayoutEditorPlayerController::OnGridInitialized);
			}

			break;
		}
	}
}

void ALayoutEditorPlayerController::OnGridInitialized()
{
	// Move camera to the grid center
	FVector GridCenter = LayoutGrid->GetWorldGridCenter();

	if (CameraPawn)
	{
		CameraPawn->SetActorLocation(GridCenter);
	}
}

void ALayoutEditorPlayerController::DeprojectMouse()
{
	if (IsBuildModeActive() == false || LayoutGrid == nullptr)
	{
		return;
	}

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
	{
		if (Hit.GetActor()->ActorHasTag(FName("TurretWall")))
		{
			if (LayoutGrid)
			{
				LayoutGrid->RequestResetPreviewWall();
			}
		}
		else if (Hit.GetActor()->ActorHasTag(FName("LayoutGrid")))
		{
			if (GameMode && GameMode->CanPlaceTurretWall() && LayoutGrid)
			{
				LayoutGrid->RequestPreviewWall(Hit.Location);
			}
		}
	}
}
