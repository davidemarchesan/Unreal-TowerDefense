// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "TopDownCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Turrets/TurretBase.h"

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				InputSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	CameraPawn = Cast<ATopDownCamera>(GetPawn());

	GetViewportSize(ViewportX, ViewportY);

}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (ZoomAction)
		{
			EnhancedInput->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::ZoomCamera);
		}

		if (ConfirmAction)
		{
			EnhancedInput->BindAction(ConfirmAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::PlaceTurret);
		}
	}
}

void ATopDownPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCamera(DeltaTime);

	MovePreviewTurret(DeltaTime);
}

void ATopDownPlayerController::RequestBuildTurret()
{
	UE_LOG(LogTemp, Warning, TEXT("controller: RequestBuildTurret"));

	bIsPlacingTurret = true;

	// Reset preview
	if (PreviewTurret)
	{
		PreviewTurret->Destroy();
		PreviewTurret = nullptr;
	}

	PreviewTurret = GetWorld()->SpawnActor<ATurretBase>(TurretBluePrintClass, FVector::ZeroVector, FRotator::ZeroRotator);

	if (PreviewTurret)
	{
		PreviewTurret->SetActorEnableCollision(false);
		for (UActorComponent* Component : PreviewTurret->GetComponents())
		{
			if (UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Component))
			{
				Primitive->SetRenderCustomDepth(true); // Semi-transparent preview
			}
		}
	}

}

void ATopDownPlayerController::MovePreviewTurret(float DeltaTime)
{
	if (bIsPlacingTurret == false || PreviewTurret == nullptr || PreviewTurret->IsPendingKillPending())
	{
		return;
	}

	FVector WorldLocation, WorldDirection;
	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FHitResult Hit;
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 4000.f);

		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
		{
			PreviewTurret->SetActorLocation(Hit.Location);
			UE_LOG(LogTemp, Warning, TEXT("Spawning turret"));
		}
	}
}

void ATopDownPlayerController::ZoomCamera(const FInputActionValue& Value)
{

	if (CameraPawn == nullptr)
	{
		return;
	}

	float AxisValue = Value.Get<float>();
	CameraPawn->Zoom(AxisValue);

}

void ATopDownPlayerController::PlaceTurret()
{
	if (bIsPlacingTurret == false || PreviewTurret == nullptr || PreviewTurret->IsPendingKillPending())
	{
		return;
	}

	FVector Location = PreviewTurret->GetActorLocation();

	GetWorld()->SpawnActor<ATurretBase>(TurretBluePrintClass, Location, FRotator::ZeroRotator);

	// Remove preview
	PreviewTurret->Destroy();
	PreviewTurret = nullptr;

	bIsPlacingTurret = false;
}

void ATopDownPlayerController::MoveCamera(float DeltaTime)
{
	if (CameraPawn == nullptr)
	{
		return;
	}

	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);

	/*UE_LOG(LogTemp, Warning, TEXT("mouse x %f y %f"), MouseX, MouseY);*/

	// Outside of the window
	if (
		MouseX > ViewportX
		|| MouseX < 0.f
		|| MouseY > ViewportY
		|| MouseY < 0.f
		)
	{
		return;
	}

	FVector MovingDirection = FVector::ZeroVector;

	// Axis are inverted, so when I want to move horizontally
	// we move the Y camera axis
	if (MouseX < EdgeScrollSize)
	{
		MovingDirection.Y = -1.f;
	}
	else if (MouseX > (ViewportX - EdgeScrollSize))
	{
		MovingDirection.Y = 1.f;
	}

	if (MouseY < EdgeScrollSize)
	{
		MovingDirection.X = 1.f;
	}
	else if (MouseY > (ViewportY - EdgeScrollSize))
	{
		MovingDirection.X = -1.f;
	}

	if (MovingDirection.IsZero() == false)
	{
		MovingDirection.Normalize();
		CameraPawn->Move(MovingDirection, DeltaTime);
	}
}
