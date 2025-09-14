// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "TowerDefense/UI/HealthBarWidget.h"
#include "AIModule.h"
#include "AIController.h"
#include "NavigationSystem.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		//FVector TargetLocation(400.f, 1270.f, 0.f);
		FVector TargetLocation(0.f, 0.f, 0.f);
		//EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(TargetLocation);

		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		FNavLocation Projected;
		if (NavSys && NavSys->ProjectPointToNavigation(TargetLocation, Projected))
		{
			EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(Projected.Location, 1.f);
			UE_LOG(LogTemp, Warning, TEXT("Projected.Location %s"), *Projected.Location.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Moving ai to center result %d"), Result);
		}



	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("no ai controller"));
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
	//UE_LOG(LogTemp, Warning, TEXT("Enemy: i took %f damage and my health is now %f"), Damage, Health);

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
		//UE_LOG(LogTemp, Warning, TEXT("Im dead, notifying all the turrets"));
		// Notify turrets that I'm dead
		OnEnemyDeath.Broadcast(this);

		Destroy();
	}
}

