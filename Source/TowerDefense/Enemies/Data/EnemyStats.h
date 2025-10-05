#pragma once

#include "CoreMinimal.h"
#include "EnemyStats.generated.h"

USTRUCT(BlueprintType)
struct FEnemyStats : public FTableRowBase
{

	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	FName ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float RateOfFire = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float Range = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float Speed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float Reward = 100.f;
};
