// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBase.h"
#include "Components/StaticMeshComponent.h"
#include "Data/TurretDataAsset.h"
#include "TowerDefense/Enemies/EnemyPawn.h"

// Sets default values
ATurretBase::ATurretBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATurretBase::BeginPlay()
{
	Super::BeginPlay();

	if (TurretData)
	{
		DetectionSphere->SetSphereRadius(TurretData->Stats.Range);
		UE_LOG(LogTemp, Warning, TEXT("range %f"), TurretData->Stats.Range);

		if (bListenForEnemies)
		{
			DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATurretBase::OnEnemyEnterRange);
			DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATurretBase::OnEnemyExitRange);
		}
	}

	// SetPreview(true);
}

// Called every frame
void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (bIsPreview == true)
	// {
	// 	return;
	// }
	//
	// if (CurrentTarget && CurrentTarget->IsPendingKillPending() == false && bTargetLock == true)
	// {
	// 	FRotator LookAtRotation = (CurrentTarget->GetActorLocation() - TurretParent->GetComponentLocation()).Rotation();
	// 	LookAtRotation.Pitch = 0.f;
	// 	LookAtRotation.Roll = 0.f;
	// 	
	//
	// 	FRotator NewRotation = FMath::RInterpTo(TurretParent->GetComponentRotation(), LookAtRotation, DeltaTime, RotationSpeed);
	// 	TurretParent->SetWorldRotation(NewRotation);
	// }
}

void ATurretBase::SetPreview(bool _bIsPreview)
{
	// bIsPreview = _bIsPreview;
	//
	// if (bIsPreview == false && PreviewMaterial)
	// {
	// 	TArray<AActor*> OverlappingActors;
	// 	DetectionSphere->GetOverlappingActors(OverlappingActors, AEnemyPawn::StaticClass());
	// }
}

void ATurretBase::Fire()
{
	// if (bIsPreview == true)
	// {
	// 	return;
	// }
	//
	// if (CurrentTarget && CurrentTarget->IsPendingKillPending() == false)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Turret: Fire with damage %f"), Damage);
	// 	CurrentTarget->ApplyDamage(Damage);
	// }
	// else
	// {
	// 	//UE_LOG(LogTemp, Warning, TEXT("Turret: Firing at invalid target, clearing timer"));
	// 	GetWorldTimerManager().ClearTimer(FireTimerHandle);
	// }
}

void ATurretBase::CheckForFiring()
{
	// if (bIsPreview == true)
	// {
	// 	return;
	// }
	//
	// UE_LOG(LogTemp, Warning, TEXT("Check for firing"));
	// if (EnemiesInRange.Num() > 0)
	// {
	// 	// Targeting logic
	// 	CurrentTarget = EnemiesInRange[0];
	//
	// 	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurretBase::Fire, 1.f / FireRate, true);
	// 	bTargetLock = true;
	// }
	// else
	// {
	// 	GetWorldTimerManager().ClearTimer(FireTimerHandle);
	// 	bTargetLock = false;
	// }
}

void ATurretBase::OnEnemyEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if (bIsPreview == true && bListenForEnemies == false)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Something entered my range! %s"), *OtherActor->GetName());

	if (AEnemyPawn* Enemy = Cast<AEnemyPawn>(OtherActor))
	{
		EnemiesInRange.AddUnique(Enemy);
		Enemy->OnEnemyDeath.AddDynamic(this, &ATurretBase::OnEnemyDeath);
	}
}

void ATurretBase::OnEnemyExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bIsPreview == true && bListenForEnemies == false)
	{
		return;
	}

	if (AEnemyPawn* Enemy = Cast<AEnemyPawn>(OtherActor))
	{
		EnemiesInRange.Remove(Enemy);
		// CheckForFiring();
	}
}

void ATurretBase::OnEnemyDeath(AEnemyPawn* Enemy)
{
	UE_LOG(LogTemp, Warning, TEXT("An enemy i was targetin is dead"));
}
