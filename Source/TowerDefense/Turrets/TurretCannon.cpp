// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretCannon.h"

ATurretCannon::ATurretCannon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretParent = CreateDefaultSubobject<USceneComponent>(TEXT("TurretParent"));
	TurretParent->SetupAttachment(RootComponent);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(TurretParent);
	
	TurretCannonParent = CreateDefaultSubobject<USceneComponent>(TEXT("TurretCannonParent"));
	TurretCannonParent->SetupAttachment(TurretParent);
	
	TurretCannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretCannonMesh"));
	TurretCannonMesh->SetupAttachment(TurretCannonParent);

	bListenForEnemies = true;
}
