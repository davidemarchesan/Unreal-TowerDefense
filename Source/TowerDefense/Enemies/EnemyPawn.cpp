// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AIController.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemyPawn::SetDestination(FVector Location)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(Location);
	}
}

void AEnemyPawn::ApplyDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Enemy: i took %f damage and my health is now %f"), Damage, Health);

	// if (HealthBarWidget)
	// {
	// 	if (UHealthBarWidget* Widget = Cast<UHealthBarWidget>(HealthBarWidget->GetUserWidgetObject()))
	// 	{
	// 		Widget->SetHealthPercent(Health / MaxHealth);
	// 	}
	//
	// 	HealthBarWidget->SetVisibility(Health < MaxHealth);
	// }

	if (Health <= 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Im dead, notifying all the turrets"));
		// Notify turrets that I'm dead
		OnEnemyDeath.Broadcast(this);

		Destroy();
	}
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

