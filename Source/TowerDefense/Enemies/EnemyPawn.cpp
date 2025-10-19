// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AIController.h"
#include "Components/WidgetComponent.h"
#include "TowerDefense/GameModes/RunGameMode.h"
#include "TowerDefense/GameStates/RunGameState.h"
#include "TowerDefense/UI/Widgets/HealthBarWidgetWrapper.h"

FOnAnyEnemyDeath AEnemyPawn::OnAnyEnemyDeath;

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

	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(RootComponent);
	HealthBarComponent->SetDrawSize(FVector2D(100, 20));
	HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarComponent->SetWidgetClass(UHealthBarWidgetWrapper::StaticClass());

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

	if (!Stats || Health <= 0.f)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);
	
	Health = FMath::Clamp(Health - Damage, 0.f, Stats->Health);

	if (HealthBarComponent && Stats)
	{
		if (UHealthBarWidgetWrapper* Widget = Cast<UHealthBarWidgetWrapper>(HealthBarComponent->GetUserWidgetObject()))
		{
			Widget->SetHealthPercent(Health / Stats->Health);
		}
	}

	if (Health <= 0.f)
	{
		Die();
	}
}

void AEnemyPawn::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Im dead, notifying all the turrets"));
	// Notify subscribers that I'm dead
	OnEnemyDeath.Broadcast(this);
	OnAnyEnemyDeath.Broadcast(this);
		
	Destroy();
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<ARunGameMode>();

	GameState = GetWorld()->GetGameState<ARunGameState>();

	if (GameMode && EnemyID.IsValid() && EnemyID.IsNone() == false)
	{
		Stats = GameMode->GetEnemyStats(EnemyID);

		if (Stats)
		{
			Health = Stats->Health;

			if (MovementComponent)
			{
				MovementComponent->MaxSpeed = Stats->Speed;
			}
		}
	}
	
	
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

