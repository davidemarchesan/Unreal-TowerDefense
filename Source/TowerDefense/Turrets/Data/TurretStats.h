#pragma once

#include "CoreMinimal.h"
#include "TurretStats.generated.h"

USTRUCT(BlueprintType)
struct FTurretStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	float Range = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	float Price = 100.f;
};
