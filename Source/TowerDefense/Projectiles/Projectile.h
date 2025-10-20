// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class TOWERDEFENSE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;
	
	float Speed = 100.f;
	float Damage = 100.f;

public:

	void InitProjectile(AActor* _Target, AActor* _Owner, float _Speed, float _Damage);
	bool UpdateProjectile(float DeltaTime);
	void Deactivate();

	bool IsActive() const { return bActive; }

private:

	UPROPERTY()
	AActor* Target = nullptr;
	
	bool bActive = false;

};
