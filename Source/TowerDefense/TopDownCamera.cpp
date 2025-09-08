// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"

// Sets default values
ATopDownCamera::ATopDownCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;

	DesiredArmLength = SpringArm->TargetArmLength; // Initialize

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ATopDownCamera::BeginPlay()
{
	Super::BeginPlay();

	DesiredArmLength = SpringArm->TargetArmLength;	
}

// Called every frame
void ATopDownCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateZoom(DeltaTime);

}

void ATopDownCamera::Zoom(float Value)
{
	DesiredArmLength = FMath::Clamp(DesiredArmLength - Value * ZoomSpeed, MinZoom, MaxZoom);
}

void ATopDownCamera::Move(FVector Direction, float DeltaTime)
{
	Direction.Normalize();
	FVector Move = FVector(Direction.X, Direction.Y, 0.f) * CameraSpeed + DeltaTime;
	AddActorWorldOffset(Move, true);
}

void ATopDownCamera::UpdateZoom(float DeltaTime)
{
	// Lerp camera zoom
	if (FMath::IsNearlyEqual(SpringArm->TargetArmLength, DesiredArmLength, 0.1f))
	{
		return;
	}

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, DesiredArmLength, DeltaTime, InterpSpeed);
}
