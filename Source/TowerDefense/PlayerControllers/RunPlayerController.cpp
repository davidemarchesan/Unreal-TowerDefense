// Fill out your copyright notice in the Description page of Project Settings.


#include "RunPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TowerDefense/Input/Config/CameraInputConfig.h"
#include "InputActionValue.h"
#include "TowerDefense/GameCamera.h"
#include "TowerDefense/TowerDefenseGameInstance.h"
#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/GameStates/RunGameState.h"
#include "TowerDefense/Input/Config/RunInputConfig.h"
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
			if (RunMappingContext)
			{
				InputSystem->AddMappingContext(RunMappingContext, 1);
			}
			if (CameraMappingContext)
			{
				InputSystem->AddMappingContext(CameraMappingContext, 1);
			}
		}
	}

	HUD = Cast<ARunHUD>(GetHUD());

	GameMode = Cast<ARunGameMode>(GetWorld()->GetAuthGameMode());
	InitializeToolbarSlots();

	GameState = Cast<ARunGameState>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->OnBuildWallModeToggle.AddDynamic(this, &ARunPlayerController::OnBuildWallModeToggle);
		GameState->OnBuildTurretModeToggle.AddDynamic(this, &ARunPlayerController::OnBuildTurretModeToggle);
	}

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
		if (RunInputConfig)
		{
			EnhancedInput->BindAction(RunInputConfig->IA_PrimaryAction, ETriggerEvent::Triggered, this,
			                          &ARunPlayerController::PrimaryAction);
			
			EnhancedInput->BindAction(RunInputConfig->IA_BuildWall, ETriggerEvent::Triggered, this,
			                          &ARunPlayerController::RequestToggleBuildWallMode);

			EnhancedInput->BindAction(RunInputConfig->IA_BuildTurret_Slot2, ETriggerEvent::Triggered, this,
									  &ARunPlayerController::RequestToggleBuildTurretMode_Slot2);

			EnhancedInput->BindAction(RunInputConfig->IA_BuildTurret_Slot3, ETriggerEvent::Triggered, this,
									  &ARunPlayerController::RequestToggleBuildTurretMode_Slot3);
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

	DeprojectPointer();
}

void ARunPlayerController::InitializeToolbarSlots()
{
	if (!GameMode)
	{
		return;
	}

	ToolbarSlots.Add(FToolbarSlot(1, GameMode->GameModeMetas->WallPrice, FText::FromName(TEXT("Wall")), FName("wall")));

	UDataTable* TurretDataTable = GameMode->TurretDataTable;
	TArray<FName> RowNames = TurretDataTable->GetRowNames();
	
	for (int32 i = 0; i < RowNames.Num(); i++)
	{
		FTurretStats* TurretStats = TurretDataTable->FindRow<FTurretStats>(RowNames[i], TEXT("Lookup Turret Stats"));
		if (!TurretStats)
		{
			continue;
		}
		
		ToolbarSlots.Add(FToolbarSlot(i + 2, TurretStats->Price, FText::FromName(TurretStats->ID), TurretStats->ID));
	}
	
}

void ARunPlayerController::PrimaryAction()
{

	if (GameMode)
	{

		if (bIsBuildWallMode == true)
		{
			FHitResult Hit;
			if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
			{
				if (Hit.GetActor()->ActorHasTag(FName("TurretWall")))
				{
					if (const AWall* TurretWall = Cast<AWall>(Hit.GetActor()))
					{
						GameMode->RequestWallRemoval(TurretWall->Col, TurretWall->Row);
					}
				}
				else if (Hit.GetActor()->ActorHasTag(FName("LayoutGrid")))
				{
					GameMode->RequestWallBuild(Hit.Location);
				}
			}
		}

		if (bIsBuildTurretMode == true)
		{
			FHitResult Hit;
			if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
			{
				if (Hit.GetActor()->ActorHasTag(FName("TurretWall")))
				{
					if (AWall* TurretWall = Cast<AWall>(Hit.GetActor()))
					{
						FVector SocketLocation = TurretWall->GetTurretSocketLocation();
						GameMode->RequestTurretBuild(TEXT("Minigun"), SocketLocation);
					}
				}
			}
		}
	}
}

void ARunPlayerController::SkipSetupPhase()
{
	if (GameState)
	{
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

void ARunPlayerController::RequestToggleBuildTurretMode_Slot2()
{
	RequestToggleBuildTurretMode(2);
}

void ARunPlayerController::RequestToggleBuildTurretMode_Slot3()
{
	RequestToggleBuildTurretMode(3);
}

void ARunPlayerController::RequestToggleBuildWallMode()
{
	if (GameMode)
	{
		GameMode->RequestToggleBuildWallMode();
	}
}

void ARunPlayerController::OnBuildWallModeToggle(bool _bIsBuildWallMode)
{
	bIsBuildWallMode = _bIsBuildWallMode;
}

void ARunPlayerController::RequestToggleBuildTurretMode(const int32 SlotNumber)
{
	if (GameMode && ToolbarSlots.Num() > 0)
	{

		FToolbarSlot* FoundSlot = ToolbarSlots.FindByPredicate([&](const FToolbarSlot& ToolbarSlot)
		{
			return ToolbarSlot.Key == SlotNumber;
		});

		if (FoundSlot != nullptr)
		{
			// FoundSlot->ID;
			GameMode->RequestToggleBuildTurretMode(FoundSlot->ID);
		}
		
	}
}

void ARunPlayerController::OnBuildTurretModeToggle(bool _bIsBuildTurretMode)
{
	bIsBuildTurretMode = _bIsBuildTurretMode;
}

void ARunPlayerController::DeprojectPointer()
{
	if (!GameMode)
	{
		return;
	}

	if (bIsBuildWallMode == false && bIsBuildTurretMode == false)
	{
		return;
	}

	if (bIsBuildWallMode == true)
	{
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
		{
			if (Hit.GetActor()->ActorHasTag(FName("TurretWall")))
			{
				GameMode->RequestResetPreviewWall();
			}
			else if (Hit.GetActor()->ActorHasTag(FName("LayoutGrid")))
			{
				GameMode->RequestWallPreview(Hit.Location);
			}
		}
	}

	if (bIsBuildTurretMode == true)
	{
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
		{
			if (Hit.GetActor()->ActorHasTag(FName("TurretWall")))
			{
				if (AWall* TurretWall = Cast<AWall>(Hit.GetActor()))
				{
					// UE_LOG(LogTemp, Warning, TEXT("Im pointing to turret wall in position %d %d"), TurretWall->Col, TurretWall->Row);
	
					FVector SocketLocation = TurretWall->GetTurretSocketLocation();
					GameMode->RequestTurretPreview("Cannon", SocketLocation);
					// UE_LOG(LogTemp, Warning, TEXT("SocketLocation: %s"), *SocketLocation.ToString());
				}
			}
			else if (Hit.GetActor()->ActorHasTag(FName("LayoutGrid")))
			{
				GameMode->RequestResetPreviewTurret();
			}
		}
	}
	
}
