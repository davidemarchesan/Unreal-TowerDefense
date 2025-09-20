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
#include "TowerDefense/UI/LayoutEditor/LayoutEditorHUD.h"

void ALayoutEditorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
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

}

void ALayoutEditorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (LayoutEditorInputConfig)
		{
			EnhancedInput->BindAction(LayoutEditorInputConfig->IA_PrimaryAction, ETriggerEvent::Triggered, this, &ALayoutEditorPlayerController::PrimaryAction);
			
			EnhancedInput->BindAction(LayoutEditorInputConfig->IA_EnterBuildMode, ETriggerEvent::Triggered, this, &ALayoutEditorPlayerController::ToggleBuildMode);
		}

		if (CameraInputConfig)
		{
			EnhancedInput->BindAction(CameraInputConfig->IA_MoveCamera, ETriggerEvent::Triggered, this, &ALayoutEditorPlayerController::MoveCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_MoveCamera, ETriggerEvent::Completed, this, &ALayoutEditorPlayerController::MoveCamera);
		
			EnhancedInput->BindAction(CameraInputConfig->IA_RotateCamera, ETriggerEvent::Triggered, this, &ALayoutEditorPlayerController::RotateCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_RotateCamera, ETriggerEvent::Completed, this, &ALayoutEditorPlayerController::RotateCamera);
			
			EnhancedInput->BindAction(CameraInputConfig->IA_ZoomCamera, ETriggerEvent::Triggered, this, &ALayoutEditorPlayerController::ZoomCamera);
			EnhancedInput->BindAction(CameraInputConfig->IA_ZoomCamera, ETriggerEvent::Completed, this, &ALayoutEditorPlayerController::ZoomCamera);
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
	if (LayoutGrid && IsBuildModeActive())
	{
		LayoutGrid->RequestWallBuild();
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
				UE_LOG(LogTemp, Warning, TEXT("PLAYER CONTROLLER: GRID ALREADY INIT"));
				OnGridInitialized();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("PLAYER CONTROLLER: ADD DYNAMIC"));
				LayoutGrid->OnGridInitialized.AddDynamic(this, &ALayoutEditorPlayerController::OnGridInitialized);
			}
			
			break;
		}
	}
}

void ALayoutEditorPlayerController::OnGridInitialized()
{

	FVector GridCenter = LayoutGrid->GetWorldGridCenter();

	if (CameraPawn)
	{
		CameraPawn->SetActorLocation(GridCenter);
	}

}

void ALayoutEditorPlayerController::DeprojectMouse()
{
	if (LayoutGrid == nullptr || IsBuildModeActive() == false) return;

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
	{
		LayoutGrid->RequestPreview(Hit.Location);
	}

}
