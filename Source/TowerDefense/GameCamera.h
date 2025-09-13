// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameCamera.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOWERDEFENSE_API AGameCamera : public APawn
{
	GENERATED_BODY()

public:

	AGameCamera();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RequestMove(FVector2D Direction);

	void RequestRotation(float Direction);

	void RequestZoom(float Direction);

protected:

	virtual void BeginPlay() override;

private:

	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// Movement
	void UpdateLocation(float DeltaTime);

	FVector2D MovingDirection = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 100.f;

	// Rotation
	void UpdateRotation(float DeltaTime);

	float RotationDirection = 0.f;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationSpeed = 100.f;

	// Zoom
	void UpdateZoom(float DeltaTime);

	float DesiredArmLength;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float ZoomSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float ZoomInterpSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Zoom");
	float MinZoom = 10.f;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float MaxZoom = 100.f;

};
