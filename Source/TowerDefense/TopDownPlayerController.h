// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "TopDownCamera.h"

#include "TopDownPlayerController.generated.h"

class ATurretBase;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* ConfirmAction;

	UPROPERTY(EditAnywhere, Category="Turrets")
	TSubclassOf<ATurretBase> TurretBluePrintClass;

	void RequestBuildTurret();

private: 

	ATopDownCamera* CameraPawn;

	void ZoomCamera(const FInputActionValue& Value);

	void PlaceTurret();

	float EdgeScrollSize = 10.0f;

	int32 ViewportX;
	int32 ViewportY;

	void MoveCamera(float DeltaTime);

	bool bIsPlacingTurret = false;

	class ATurretBase* PreviewTurret = nullptr;

	void MovePreviewTurret(float DeltaTime);
	
};
