// Fill out your copyright notice in the Description page of Project Settings.


#include "Nexus.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "TowerDefense/Enemies/EnemyPawn.h"
#include "TowerDefense/GameStates/RunGameState.h"
#include "TowerDefense/UI/Widgets/HealthBarWidgetWrapper.h"

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
	HealthBarWidget->SetDrawSize(FVector2D(100, 20));
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetWidgetClass(UHealthBarWidgetWrapper::StaticClass());
	HealthBarWidget->SetVisibility(false);

}

// Called when the game starts or when spawned
void ANexus::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("ANexus beginplay"));
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<ARunGameState>();

	Health = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("Health initial: %f"), Health);
	
}

// Called every frame
void ANexus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANexus::TakeDamageFromEnemy(float EnemyHealth)
{

	// Health = FMath::Clamp(Health - EnemyHealth, 0.f, MaxHealth);
	Health = FMath::Max(0.f, (Health - EnemyHealth));
	UE_LOG(LogTemp, Warning, TEXT("took %f damage, so Health: %f"), EnemyHealth, Health);

	if (HealthBarWidget && EnemyHealth)
	{
		if (UHealthBarWidgetWrapper* Widget = Cast<UHealthBarWidgetWrapper>(HealthBarWidget->GetUserWidgetObject()))
		{
			Widget->SetHealthPercent(Health / MaxHealth);
		}
	
		HealthBarWidget->SetVisibility(true);
	}

	if (GameState)
	{
		GameState->ReducePlayerHealth(EnemyHealth);
	}

	if (Health <= 0.f)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Main base is dead, end of the game"));
	}

}

void ANexus::OnEnemyEnterCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// UE_LOG(LogTemp, Warning, TEXT("An anemy has touched me"));

	if (AEnemyPawn* Enemy = Cast<AEnemyPawn>(OtherActor))
	{
		TakeDamageFromEnemy(Enemy->Health);

		Enemy->Destroy();
	}

}
