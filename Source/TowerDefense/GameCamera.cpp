// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SceneRoot->SetMobility(EComponentMobility::Movable);
	RootComponent = SceneRoot;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(SceneRoot);
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();

	DesiredArmLength = SpringArm->TargetArmLength;
	
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation(DeltaTime);

	UpdateRotation(DeltaTime);

	UpdateZoom(DeltaTime);

}

// Called to bind functionality to input
void AGameCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGameCamera::RequestMove(FVector2D Direction)
{
	Direction.Normalize();
	MovingDirection = Direction;
}

void AGameCamera::RequestRotation(float Direction)
{
	RotationDirection = Direction;
}

void AGameCamera::RequestZoom(float Direction)
{
	DesiredArmLength = FMath::Clamp(DesiredArmLength - Direction * ZoomSpeed, MinZoom, MaxZoom);
}

void AGameCamera::UpdateLocation(float DeltaTime)
{

	if (MovingDirection.IsNearlyZero(0.1f) == false)
	{
		FVector Move = FVector(MovingDirection.X, MovingDirection.Y, 0.f) * MovementSpeed * DeltaTime;
		AddActorLocalOffset(Move, true);
	}

}

void AGameCamera::UpdateRotation(float DeltaTime)
{

	if (FMath::IsNearlyZero(RotationDirection) == false)
	{
		FRotator DeltaRotation = FRotator(0.f, RotationDirection * RotationSpeed * DeltaTime, 0.f);
		AddActorWorldRotation(DeltaRotation);
	}

}

void AGameCamera::UpdateZoom(float DeltaTime)
{
	if (FMath::IsNearlyEqual(SpringArm->TargetArmLength, DesiredArmLength, 0.1f))
	{
		return;
	}

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, DesiredArmLength, DeltaTime, ZoomInterpSpeed);

}
