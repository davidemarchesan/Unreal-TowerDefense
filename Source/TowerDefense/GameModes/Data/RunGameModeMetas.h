#pragma once

#include "CoreMinimal.h"
#include "RunGameModeMetas.generated.h"

USTRUCT(BlueprintType)
struct FRunGameModeMetas : public FTableRowBase
{

	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Metas")
	float PlayerInitialHealth = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Metas")
	float PlayerInitialCoins = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Metas")
	float WallPrice = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Metas")
	int32 FirstSetupPhaseTimer = 60;

	UPROPERTY(EditDefaultsOnly, Category = "Metas")
	int32 SetupPhaseTimer = 20;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 GridCols = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 GridRows = 10;
	
};
