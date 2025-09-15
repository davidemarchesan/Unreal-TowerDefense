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

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		//FVector TargetLocation(0.f, 0.f, 0.f);
		FVector TargetLocation(459.f, 900.f, 0.f);
		EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(TargetLocation);
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

