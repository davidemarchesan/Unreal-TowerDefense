// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine/TimerHandle.h"
#include "TurretBase.generated.h"

class AEnemyBase;
class UPrimitiveComponent;

UCLASS()
class TOWERDEFENSE_API ATurretBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	TArray<AEnemyBase*> EnemiesInRange;

	UPROPERTY()
	AEnemyBase* CurrentTarget;

	bool bTargetLock = false;

	UFUNCTION()
	void OnEnemyEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEnemyExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnEnemyDeath(AEnemyBase* Enemy);

};
