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
};
