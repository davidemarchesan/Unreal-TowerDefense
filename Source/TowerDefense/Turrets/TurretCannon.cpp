// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretCannon.h"

#include "Data/TurretDataAsset.h"
#include "TowerDefense/Enemies/EnemyPawn.h"

ATurretCannon::ATurretCannon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretParent = CreateDefaultSubobject<USceneComponent>(TEXT("TurretParent"));
	TurretParent->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(TurretParent);

	TurretCannonParent = CreateDefaultSubobject<USceneComponent>(TEXT("TurretCannonParent"));
	TurretCannonParent->SetupAttachment(TurretParent);

	TurretCannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretCannonMesh"));
	TurretCannonMesh->SetupAttachment(TurretCannonParent);

	bListenForEnemies = true;
}

void ATurretCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateTurret(DeltaTime);
}

void ATurretCannon::StartFireTimer()
{
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurretCannon::Fire, 1.f / TurretData->Stats.RateOfFire, true);
}

void ATurretCannon::StopFireTimer()
{
	if (FireTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
	}
}

void ATurretCannon::Fire()
{
	if (bIsPreview == true || CurrentTarget == nullptr)
	{
		StopFireTimer();
		return;
	}

	if (CurrentTarget && CurrentTarget->IsPendingKillPending() == false)
	{
		CurrentTarget->ApplyDamage(TurretData->Stats.Damage);
	}
	else
	{
		ResetTarget();
	}
}

void ATurretCannon::SelectTarget()
{
	if (CurrentTarget != nullptr)
	{
		return;
	}

	if (EnemiesInRange.Num() > 0)
	{
		CurrentTarget = EnemiesInRange[0];
		StartFireTimer();
	}
	else
	{
		ResetTarget();
	}
}

void ATurretCannon::ResetTarget()
{
	CurrentTarget = nullptr;
	StopFireTimer();
}

void ATurretCannon::RotateTurret(float DeltaTime)
{
	if (bIsPreview == true || CurrentTarget == nullptr)
	{
		return;
	}

	if (CurrentTarget && CurrentTarget->IsPendingKillPending() == false)
	{
		FRotator LookAtRotation = (CurrentTarget->GetActorLocation() - TurretParent->GetComponentLocation()).Rotation();
		LookAtRotation.Pitch = 0.f;
		LookAtRotation.Roll = 0.f;


		const FRotator NewRotation = FMath::RInterpTo(TurretParent->GetComponentRotation(), LookAtRotation, DeltaTime, RotationSpeed);
		TurretParent->SetWorldRotation(NewRotation);
	}
}

void ATurretCannon::OnEnemyEnterRange(AEnemyPawn* Enemy)
{
	Super::OnEnemyEnterRange(Enemy);
	
	SelectTarget();
}
