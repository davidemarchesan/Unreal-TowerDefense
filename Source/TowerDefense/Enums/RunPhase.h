#pragma once

#include "CoreMinimal.h"
#include "RunPhase.generated.h"

UENUM(BlueprintType)
enum class ERunPhase : uint8
{
	BuyAndBuild UMETA(DisplayName = "Buy and Build"),
	Wave UMETA(DisplayName = "Wave"),
};
