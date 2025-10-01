// Fill out your copyright notice in the Description page of Project Settings.


#include "Nexus.h"
#include "Components/BoxComponent.h"
#include "TowerDefense/UI/HealthBarWidget.h"
#include "Components/WidgetComponent.h"
#include "TowerDefense/Enemies/EnemyPawn.h"

// Sets default values
ANexus::ANexus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

	// Collision
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	BoxComponent->SetGenerateOverlapEvents(true);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ANexus::OnEnemyEnterCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetGenerateOverlapEvents(false); // Avoid mesh collision

	// UI
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetDrawSize(FVector2D(100, 10));
	HealthBarWidget->SetVisibility(false);

}

// Called when the game starts or when spawned
void ANexus::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
}

// Called every frame
void ANexus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANexus::TakeDamageFromEnemy(float EnemyHealth)
{

	Health = FMath::Clamp(Health - EnemyHealth, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

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
		UE_LOG(LogTemp, Warning, TEXT("Main base is dead, end of the game"));
	}

}

void ANexus::OnEnemyEnterCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("An anemy has touched me"));

	if (AEnemyPawn* Enemy = Cast<AEnemyPawn>(OtherActor))
	{
		TakeDamageFromEnemy(Enemy->Health);

		Enemy->Destroy();
	}

}
