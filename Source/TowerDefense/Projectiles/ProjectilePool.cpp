// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePool.h"

#include "Projectile.h"

// Sets default values
AProjectilePool::AProjectilePool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProjectilePool::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectilePool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (AProjectile* Projectile : ProjectilePool)
	{
		if (Projectile && Projectile->IsActive() == true)
		{
			Projectile->UpdateProjectile(DeltaTime);
		}
	}
}

AProjectile* AProjectilePool::GetFreeProjectile()
{
	// Get the first free projectile from pool
	for (AProjectile* Projectile : ProjectilePool)
	{
		if (Projectile && Projectile->IsHidden() == false && Projectile->IsActive() == false)
		{
			return Projectile;
		}
	}

	// Create a new projectile and add it to the pool
	if (ProjectileBluePrintClass)
	{
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrintClass, FVector::ZeroVector,
		                                                                 FRotator::ZeroRotator);
		if (NewProjectile)
		{
			RegisterProjectile(NewProjectile);
		}
		return NewProjectile;
	}

	return nullptr;
}

void AProjectilePool::RegisterProjectile(AProjectile* Projectile)
{
	if (Projectile && ProjectilePool.Contains(Projectile) == false)
	{
		ProjectilePool.Add(Projectile);
	}
}
