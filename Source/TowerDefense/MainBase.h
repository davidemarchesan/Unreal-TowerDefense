// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainBase.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class TOWERDEFENSE_API AMainBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	// Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MaxHealth = 2000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* HealthBarWidget;

private:

	void TakeDamageFromEnemy(float EnemyHealth);

	UFUNCTION()
	void OnEnemyEnterCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
