// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine/TimerHandle.h"
#include "TurretBase.generated.h"

class AEnemyPawn;
class UTurretDataAsset;
class UMaterialInterface;
class UPrimitiveComponent;
class UMaterialInstanceDynamic;

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

	void SetPreview(bool _bIsPreview);

	UPROPERTY(EditAnywhere, Category = "Stats")
	UTurretDataAsset* TurretData;

protected: 

	// Components
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DetectionSphere;
	
	bool bIsPreview = true;

	bool bListenForEnemies = false;

	bool bListenForTurrets = false;
	
	// Fire
	FTimerHandle FireTimerHandle;

	void Fire();

	void CheckForFiring();

	// Targeting
	UPROPERTY()
	TArray<AEnemyPawn*> EnemiesInRange;

	UPROPERTY()
	TArray<ATurretBase*> TurretsInRange;

	UPROPERTY()
	AEnemyPawn* CurrentTarget;

	bool bTargetLock = false;

	UFUNCTION()
	void OnEnemyEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEnemyExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnEnemyDeath(AEnemyPawn* Enemy);

};
