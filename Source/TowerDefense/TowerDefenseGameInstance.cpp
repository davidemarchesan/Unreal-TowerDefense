// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenseGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Saves/GridLayoutSave.h"

void UTowerDefenseGameInstance::SaveGridLayout(TArray<FIntPoint> &Layout)
{

	// UGridLayoutSave* GridLayoutSaveInstance = Cast<UGridLayoutSave>(
	// 	UGameplayStatics::CreateSaveGameObject(UGridLayoutSave::StaticClass())
	// );
	//
	// GridLayoutSaveInstance->Layout = Layout;
	//
	// UGameplayStatics::SaveGameToSlot(GridLayoutSaveInstance, TEXT("GridLayout"), 0);

	
}

TArray<FIntPoint> UTowerDefenseGameInstance::LoadGridLayout()
{

	// UGridLayoutSave* GridLayoutSaveInstance = Cast<UGridLayoutSave>(
	// 	UGameplayStatics::LoadGameFromSlot(TEXT("GridLayout"), 0)
	// );
	//
	// if (GridLayoutSaveInstance)
	// {
	// 	return GridLayoutSaveInstance->Layout;
	// }

	return TArray<FIntPoint>();
	
}
