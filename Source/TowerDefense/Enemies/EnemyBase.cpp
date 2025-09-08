// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "TowerDefense/UI/HealthBarWidget.h"
#include "AIModule.h"
#include "AIController.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetGenerateOverlapEvents(false); // Avoid mesh collision

	// UI
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetDrawSize(FVector2D(100, 10));
	HealthBarWidget->SetVisibility(false);

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AAIController* AIController = Cast<AAIController>(GetController());

	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving ai to center"));
		EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(FVector(1.f, 10.f, 1.f));

		UE_LOG(LogTemp, Warning, TEXT("Moving ai to center result %d"), Result);
	}
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::ApplyDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Enemy: i took %f damage and my health is now %f"), Damage, Health);

	if (HealthBarWidget)
	{
		if (UHealthBarWidget* Widget = Cast<UHealthBarWidget>(HealthBarWidget->GetUserWidgetObject()))
		{
			Widget->SetHealthPercent(Health / MaxHealth);
		}

		HealthBarWidget->SetVisibility(Health < MaxHealth);
	}

	if (Health <= 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Im dead, notifying all the turrets"));
		// Notify turrets that I'm dead
		OnEnemyDeath.Broadcast(this);

		Destroy();
	}
}

