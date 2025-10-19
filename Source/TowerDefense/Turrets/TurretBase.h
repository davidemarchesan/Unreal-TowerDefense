// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Data/TurretStats.h"
#include "Engine/TimerHandle.h"
#include "TurretBase.generated.h"

class AEnemyPawn;
class UTurretDataAsset;
class UMaterialInterface;
class UPrimitiveComponent;
class UMaterialInstanceDynamic;
class UDecalComponent;
class ARunGameMode;
class AProjectilePool;

UCLASS()
class TOWERDEFENSE_API ATurretBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurretBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetPreviewState(bool _bIsPreview);

	UPROPERTY(EditDefaultsOnly, Category = "Turret")
	FName TurretID;
	
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bShowRangeDebugSphere = false;

protected:

	ARunGameMode* GameMode;

	// Stats
	FTurretStats* Stats;

	// Components
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DetectionSphere;
	
	bool bIsPreview = true;

	bool bListenForEnemies = false;

	bool bListenForTurrets = false;

	// Range
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	UDecalComponent* RangeDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	UMaterialInterface* RangeDecalMaterial;
	
	FTimerHandle FireTimerHandle;

	void Fire();

	void CheckForFiring();

	// Projectile
	AProjectilePool* ProjectilePool;

	// Targeting
	UPROPERTY()
	TArray<AEnemyPawn*> EnemiesInRange;
	
	UPROPERTY()
	TArray<ATurretBase*> TurretsInRange;

	UPROPERTY()
	AEnemyPawn* CurrentTarget;

	bool bTargetLock = false;

	UFUNCTION()
	void OnEnemyEnterRangeDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnEnemyEnterRange(AEnemyPawn* Enemy);
	
	UFUNCTION()
	void OnEnemyExitRangeDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void OnEnemyExitRange(AEnemyPawn* Enemy);
	
	UFUNCTION()
	virtual void OnEnemyDeath(AEnemyPawn* Enemy);

};
