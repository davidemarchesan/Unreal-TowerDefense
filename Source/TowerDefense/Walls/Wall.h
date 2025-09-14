// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefense/Enums/PreviewWallState.h"
#include "Wall.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class TOWERDEFENSE_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	

	AWall();

protected: 

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

};
