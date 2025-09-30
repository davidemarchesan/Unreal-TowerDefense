// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine/TimerHandle.h"
#include "TurretBase.generated.h"

class AEnemyPawn;
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

private: 

	// Components
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* TurretParent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DetectionSphere;

	// Preview
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UMaterialInterface* PreviewMaterial;

	UMaterialInterface* BaseMaterial;
	UMaterialInterface* TurretMaterial;
	
	bool bIsPreview = true;
	
	// Stats
	UPROPERTY(EditAnywhere, Category="Stats")
	float Range = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float FireRate = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float RotationSpeed = 10.f;

	// Fire
	FTimerHandle FireTimerHandle;

	void Fire();

	void CheckForFiring();

	// Targeting
	UPROPERTY()
	TArray<AEnemyPawn*> EnemiesInRange;

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
