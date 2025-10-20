// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretCannon.h"

#include "Data/TurretDataAsset.h"
#include "TowerDefense/Enemies/EnemyPawn.h"
#include "TowerDefense/Projectiles/Projectile.h"
#include "TowerDefense/Projectiles/ProjectilePool.h"

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
	Fire();
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurretCannon::Fire, 1.f / Stats->RateOfFire,
	                                true);
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
	if (bIsPreview == true)
	{
		return;
	}

	if (CurrentTarget == nullptr)
	{
		ResetTarget();
		return;
	}

	if (CurrentTarget && CurrentTarget->IsPendingKillPending() == false)
	{
		// CurrentTarget->ApplyDamage(Stats->Damage);
		if (ProjectilePool)
		{
			AProjectile* Projectile = ProjectilePool->GetFreeProjectile();
			if (Projectile)
			{
				Projectile->SetActorLocation(GetActorLocation());
				Projectile->InitProjectile(CurrentTarget, this, Stats->ProjectileSpeed, Stats->Damage);
			}
		}
	}
	else
	{
		ResetTarget();
	}
}

void ATurretCannon::SearchForNewTarget()
{
	if (CurrentTarget != nullptr || bIsSearchingForNewTarget == true)
	{
		return;
	}

	bIsSearchingForNewTarget = true;

	if (EnemiesInRange.Num() > 0)
	{
		for (AEnemyPawn* Enemy : EnemiesInRange)
		{
			if (Enemy != nullptr && Enemy->IsPendingKillPending() == false)
			{
				CurrentTarget = Enemy;
				break;
			}
		}

		if (CurrentTarget)
		{
			StartFireTimer();
		}
	}

	bIsSearchingForNewTarget = false;
}

void ATurretCannon::ResetTarget()
{
	CurrentTarget = nullptr;
	StopFireTimer();
	SearchForNewTarget();
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


		const FRotator NewRotation = FMath::RInterpTo(TurretParent->GetComponentRotation(), LookAtRotation, DeltaTime,
		                                              RotationSpeed);
		TurretParent->SetWorldRotation(NewRotation);
	}
}

void ATurretCannon::OnEnemyEnterRange(AEnemyPawn* Enemy)
{
	Super::OnEnemyEnterRange(Enemy);
	SearchForNewTarget();
}

void ATurretCannon::OnEnemyExitRange(AEnemyPawn* Enemy)
{
	Super::OnEnemyExitRange(Enemy);

	if (Enemy != nullptr && CurrentTarget != nullptr && Enemy == CurrentTarget)
	{
		ResetTarget();
	}
}

void ATurretCannon::OnEnemyDeath(AEnemyPawn* Enemy)
{
	Super::OnEnemyDeath(Enemy);

	if (Enemy != nullptr && CurrentTarget != nullptr && Enemy == CurrentTarget)
	{
		ResetTarget();
	}
}
