// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "TowerDefense/Enemies/EnemyPawn.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionProfileName("Projectile");

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::InitProjectile(AActor* _Target, AActor* _Owner, float _Speed, float _Damage)
{
	
	Target = _Target;
	Owner = _Owner;
	Speed = _Speed;
	Damage = _Damage;

	bActive = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	
}

bool AProjectile::UpdateProjectile(float DeltaTime)
{
	if (bActive == false || !Target || Target->IsPendingKillPending())
	{
		Deactivate();
		return false;
	}

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * Speed * DeltaTime;

	SetActorLocation(NewLocation);

	if (FVector::DistSquared(NewLocation, TargetLocation) < FMath::Square(3.f))
	{

		AEnemyPawn* Enemy = Cast<AEnemyPawn>(Target);
		if (Enemy)
		{
			Enemy->ApplyDamage(Damage);
		}
		
		Deactivate();
		return false;
	}

	return true;
}

void AProjectile::Deactivate()
{
	bActive = false;

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}
