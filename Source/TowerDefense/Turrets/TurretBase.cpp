// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBase.h"
#include "Components/StaticMeshComponent.h"
#include "TowerDefense/Enemies/EnemyBase.h"

// Sets default values
ATurretBase::ATurretBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretParent = CreateDefaultSubobject<USceneComponent>(TEXT("TurretParent"));
	TurretParent->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(TurretParent);

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(RootComponent);
	DetectionSphere->SetSphereRadius(Range);

	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATurretBase::OnEnemyEnterRange);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATurretBase::OnEnemyExitRange);

}

// Called when the game starts or when spawned
void ATurretBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> OverlappingActors;
	DetectionSphere->GetOverlappingActors(OverlappingActors, AEnemyBase::StaticClass());

}

// Called every frame
void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTarget && CurrentTarget->IsPendingKillPending() == false && bTargetLock == true)
	{
		FRotator LookAtRotation = (CurrentTarget->GetActorLocation() - TurretParent->GetComponentLocation()).Rotation();
		LookAtRotation.Pitch = 0.f;
		LookAtRotation.Roll = 0.f;
		

		FRotator NewRotation = FMath::RInterpTo(TurretParent->GetComponentRotation(), LookAtRotation, DeltaTime, RotationSpeed);
		TurretParent->SetWorldRotation(NewRotation);
	}

}

void ATurretBase::Fire()
{
	if (CurrentTarget && CurrentTarget->IsPendingKillPending() == false)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Turret: Fire with damage %f"), Damage);
		CurrentTarget->ApplyDamage(Damage);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Turret: Firing at invalid target, clearing timer"));
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
	}
}

void ATurretBase::CheckForFiring()
{
	UE_LOG(LogTemp, Warning, TEXT("Check for firing"));
	if (EnemiesInRange.Num() > 0)
	{

		// Targeting logic
		CurrentTarget = EnemiesInRange[0];

		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurretBase::Fire, 1.f / FireRate, true);
		bTargetLock = true;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
		bTargetLock = false;
	}
}

void ATurretBase::OnEnemyEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Something entered my range! %s"), *OtherActor->GetName());
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);

	if (Enemy)
	{
		EnemiesInRange.AddUnique(Enemy);

		Enemy->OnEnemyDeath.AddDynamic(this, &ATurretBase::OnEnemyDeath);

		CheckForFiring();
	}
}

void ATurretBase::OnEnemyExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);

	if (Enemy) 
	{
		EnemiesInRange.Remove(Enemy);

		CheckForFiring();
	}
}

void ATurretBase::OnEnemyDeath(AEnemyBase* Enemy)
{
	UE_LOG(LogTemp, Warning, TEXT("An enemy i was targetin is dead"));
}

