// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectilePool.generated.h"

class AProjectile;

UCLASS()
class TOWERDEFENSE_API AProjectilePool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectilePool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AProjectile* GetFreeProjectile();
	void RegisterProjectile(AProjectile* Projectile);

private:

	UPROPERTY(EditDefaultsOnly, Category = "BluePrint")
	TSubclassOf<AProjectile> ProjectileBluePrintClass;

	UPROPERTY()
	TArray<AProjectile*> ProjectilePool;

};
