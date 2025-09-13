// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TopDownCamera.generated.h"

UCLASS()
class TOWERDEFENSE_API ATopDownCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATopDownCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USpringArmComponent* GetSpringArm() const { return SpringArm; }

	void Move(FVector Direction, float DeltaTime);

	void Zoom(float Value);

private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	// Camera movement
	UPROPERTY(EditAnywhere, Category = "Movement")
	float CameraSpeed = 100.f;

	// Camera Zoom
	UPROPERTY(EditAnywhere, Category="Zoom")
	float ZoomSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float InterpSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Zoom");
	float MinZoom = 10.f;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float MaxZoom = 100.f;

	float DesiredArmLength;

	void UpdateZoom(float DeltaTime); 

};
